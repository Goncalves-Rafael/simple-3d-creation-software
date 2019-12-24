#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <functional>

#include "program.h"

void Program::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

Program::Program() {
  int success;
  char *infoLog;

  windowId = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (windowId == NULL) {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
  }
  glfwMakeContextCurrent(windowId);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return;
  }

  programId = glCreateProgram();
  glViewport(0, 0, 800, 600);
  // auto cb = std::bind(&Program::framebuffer_size_callback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  glfwSetFramebufferSizeCallback(windowId, this->framebuffer_size_callback);
}

void Program::createVertexShader(const GLchar* shaderPath) {
  shaders.push_back(new Shader(shaderPath, GL_VERTEX_SHADER));
}

void Program::createFragmentShader(const GLchar* shaderPath) {
  shaders.push_back(new Shader(shaderPath, GL_FRAGMENT_SHADER));
}

void Program::use() {
  int success;
  char *infoLog;

  glAttachShader(programId, shaders[0]->getShaderId());
  glAttachShader(programId, shaders[1]->getShaderId());
  glLinkProgram(programId);

  glGetProgramiv(programId, GL_LINK_STATUS, &success);
  if(!success) {
      glGetProgramInfoLog(programId, 512, NULL, infoLog);
      std::cout << "ERROR::PROGRAM::SHADER::LINK_FAILED\n" << infoLog << std::endl;
  }

  glUseProgram(programId);
  // glDeleteShader(vertexShader);
  // glDeleteShader(fragmentShader);
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(GL_FLOAT)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  while(!glfwWindowShouldClose(windowId)) {
    // input
    if(glfwGetKey(windowId, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(windowId, true);
    glfwSwapBuffers(windowId);

    //render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw our first triangle
    glUseProgram(programId);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);


    // events
    glfwPollEvents();
  }
}
