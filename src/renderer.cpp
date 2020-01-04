
#include "renderer.h"

void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

Renderer::Renderer(int width = 800, int height = 600) {

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  int success;
  char *infoLog;

  _width = width;
  _height = height;

  _windowId = glfwCreateWindow(_width, _height, "Simcs", NULL, NULL);
  if (_windowId == NULL) {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
  }
  glfwMakeContextCurrent(_windowId);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return;
  }

  glViewport(0, 0, _width, _height);
  glfwSetFramebufferSizeCallback(_windowId, this->framebuffer_size_callback);

  _currentProgram = new Program(); // TODO
}

int Renderer::prepare(){
  const char* vertex = "src/shaders/baseVertexShader.vs";
  const char* fragment = "src/shaders/baseFragmentShader.fs";

  _currentProgram->createVertexShader(vertex);
  _currentProgram->createFragmentShader(fragment);

  glGenVertexArrays(1, &_VAO);
  glGenBuffers(1, &_VBO);

  updateProjectionMatrix();
  updateViewMatrix();
  return 1;
}

void Renderer::setProgram(Program* program) {
  _currentProgram = program;
}

int Renderer::sendData(std::vector<Object*> &objects, int verticesCount) {
  try {
    int offset = 0, size;
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*verticesCount, NULL, GL_STATIC_DRAW);

    for(int i = 0; i < objects.size(); i++) {
      size = objects[i]->getVerticesCount() * sizeof(float);
      glBufferSubData(GL_ARRAY_BUFFER, offset, size, objects[i]->getVertices());
      offset += size;
    }

    _currentProgram->use();

  } catch (std::exception e) {
    // Todo
    std::cout << "send data error" << std::endl;
    return 0;
  }
  return 1;
}


void Renderer::updateProjectionMatrix(){
  glfwGetWindowSize(_windowId, &_width, &_height);
  glm::mat4 projection;
  projection = glm::perspective(glm::radians(45.0f), float(_width)/float(_height), 0.1f, 100.0f);

  GLint projectionLoc = glGetUniformLocation(_currentProgram->getProgramId(), "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Renderer::updateViewMatrix(){
  glm::mat4 view = glm::mat4(1.0f);
  view = glm::translate(view, glm::vec3(10.0f, 28.0f, -3.0f));
  GLint viewLoc = glGetUniformLocation(_currentProgram->getProgramId(), "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}

void Renderer::draw(std::vector<Object*> &objects) {
  glUseProgram(_currentProgram->getProgramId());

  while(!glfwWindowShouldClose(_windowId)) { //TODO view loop
    // input
    processInput();


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glBindTexture(GL_TEXTURE_2D, texture->getId());
    // create transformations
    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    transform = glm::rotate(transform, (float)glfwGetTime(), glm::normalize(glm::vec3(1.0f, 1.0f, 0.0f)));
    unsigned int transformLoc = glGetUniformLocation(_currentProgram->getProgramId(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    // render container
    glBindVertexArray(_VAO);
    int offset = 0;

    for(unsigned int i = 0; i < objects.size(); i++) {
      glDrawArrays(GL_TRIANGLES, offset, objects[i]->getVerticesCount()/_VERTEX_INFO_SIZE);
    }


    // events
    glfwSwapBuffers(_windowId);
    glfwPollEvents();
  }
  glfwTerminate();
}

void Renderer::processInput() {
  if(glfwGetKey(_windowId, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(_windowId, true);
}
