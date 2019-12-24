#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 color;\n"
    "out vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   vertexColor = vec4(color, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec4 vertexColor;"
    "void main()\n"
    "{\n"
    "   FragColor = vertexColor;\n"
    "}\n\0";



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int compileVertexShader(const char *src);
unsigned int compileFragmentShader(const char *src);
void makeTriangle();


int main () {
  unsigned int VBO1, VBO2, VAO1, VAO2;
  unsigned int vertexShader, fragmentShader;
  int success;
  char *infoLog;

  std::cout << "Hello world";
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Mac only
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return -1;
  }

  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  vertexShader = compileVertexShader(vertexShaderSource);
  fragmentShader = compileFragmentShader(fragmentShaderSource);

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if(!success) {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      std::cout << "ERROR::PROGRAM::SHADER::LINK_FAILED\n" << infoLog << std::endl;
  }

  glUseProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glGenVertexArrays(1, &VAO1);
  glGenVertexArrays(1, &VAO2);
  glGenBuffers(1, &VBO1);
  glGenBuffers(1, &VBO2);

  float vertices[] = {
    -0.5f, +0.5f, 0.0f, 1.f, 0.0f, 0.0f,
     0.5f, +0.5f, 0.0f, 0.0f, 1.f, 0.0f,
     0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.f
  };
  float vertices2[] = {
    -0.5f, -0.5f, 0.0f, 5.0, 0.0, 0.0,
     0.5f, -0.5f, 0.0f, 0.0, 5.0, 0.0,
     0.0f, .0f, 0.0f, 0.0, 0.0, 5.0
  };

  glBindVertexArray(VAO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(vertices2), vertices2);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(GL_FLOAT)));
  glEnableVertexAttribArray(1);

  // glBindVertexArray(VAO2);
  // glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  // glEnableVertexAttribArray(0);
  // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)3);
  // glEnableVertexAttribArray(1);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  glBindVertexArray(0);
  int teste = 0;
  while(!glfwWindowShouldClose(window)) {
    // input
    processInput(window);
    glfwSwapBuffers(window);

    //render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw our first triangle
    if(teste < 50) {
      glUseProgram(shaderProgram);
      glBindVertexArray(VAO1);
      glDrawArrays(GL_POINTS, 0, 3);
      teste++;
    } else if (teste < 100){
      glUseProgram(shaderProgram);
      glBindVertexArray(VAO1);
      glDrawArrays(GL_LINE_LOOP, 0, 3);
      teste++;
    } else if (teste < 150){
      glUseProgram(shaderProgram);
      glBindVertexArray(VAO1);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      teste++;
    } else {
      teste = 0;
    }


    // events
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


unsigned int compileVertexShader(const char *src) {
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertexShader, 1, &src, NULL);
  glCompileShader(vertexShader);

  glShaderSource(vertexShader, 1, &src, NULL);
  glCompileShader(vertexShader);

  // Check if shader was compiled
  int  success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if(!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  return vertexShader;
}

unsigned int compileFragmentShader(const char *src) {
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragmentShader, 1, &src, NULL);
  glCompileShader(fragmentShader);

  glShaderSource(fragmentShader, 1, &src, NULL);
  glCompileShader(fragmentShader);

  // Check if shader was compiled
  int  success;
  char infoLog[512];
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if(!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  return fragmentShader;
}
