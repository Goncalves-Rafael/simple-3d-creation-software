
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
  _currentProgram->linkShaders();
  glGenVertexArrays(1, &_VAO);
  glGenBuffers(1, &_VBO);

  glUseProgram(_currentProgram->getProgramId());
  updateProjectionMatrix();
  updateViewMatrix();
  glfwGetCursorPos(_windowId, &_xPos, &_yPos);
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 cameraDirection = glm::normalize(cameraPos);
  cameraRight = glm::normalize(glm::cross(up, cameraDirection));
  cameraUp = glm::cross(cameraDirection, cameraRight);

  return 1;
}

GLFWwindow* Renderer::getWindowId() {
  return _windowId;
}

void Renderer::setProgram(Program* program) {
  _currentProgram = program;
}

int Renderer::sendData(std::vector<Object*> &objects, int verticesCount) {
  try {
    int offset = 0, size;
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(verticesCount+30), NULL, GL_STATIC_DRAW);
    for(int i = 0; i < objects.size(); i++) {
      size = objects[i]->getVerticesCount() * sizeof(float);
      glBufferSubData(GL_ARRAY_BUFFER, offset, size, objects[i]->getVertices());
      offset += size;
    }
    sendAxisData(offset);
    _currentProgram->setAttributes();

  } catch (std::exception e) {
    // Todo
    std::cout << "send data error" << std::endl;
    return 0;
  }
  return 1;
}

void Renderer::sendAxisData(int offset) {
  float axisSize = 50.0f;
  float axis[] = {
    -axisSize, 0.0f, 0.0f, 0.0f, 0.0f,
    axisSize, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, -axisSize, 0.0f, 0.0f, 0.0f,
    0.0f, axisSize, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, -axisSize, 0.0f, 0.0f,
    0.0f, 0.0f, axisSize, 0.0f, 0.0f
  };

  glBufferSubData(GL_ARRAY_BUFFER, offset, 30*sizeof(float), axis);
}


void Renderer::updateProjectionMatrix(){
  glfwGetWindowSize(_windowId, &_width, &_height);
  glm::mat4 projection;
  projection = glm::perspective(glm::radians(45.0f), float(_width)/float(_height), 0.1f, 100.0f);

  GLint projectionLoc = glGetUniformLocation(_currentProgram->getProgramId(), "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Renderer::updateViewMatrix(){
  _view = glm::mat4(1.0f);
  _view = glm::translate(_view, glm::vec3(0.5f, -0.5f, -5.0f));
  _view = glm::rotate(_view, glm::radians(35.0f), glm::normalize(glm::vec3(0.8f, 0.4f, 0.2f)));
  GLint viewLoc = glGetUniformLocation(_currentProgram->getProgramId(), "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_view));
}

void Renderer::draw(std::vector<Object*> &objects) {

  _view = glm::lookAt(cameraPos, -cameraPos, cameraUp);
  GLint viewLoc = glGetUniformLocation(_currentProgram->getProgramId(), "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_view));
  // std::cout << _xPos << ", " << _yPos << std::endl;


  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // glBindTexture(GL_TEXTURE_2D, texture->getId());
  // create transformations
  // render container
  unsigned int modelLoc = glGetUniformLocation(_currentProgram->getProgramId(), "model");
  glBindVertexArray(_VAO);
  int offset = 0;
  for(int i = 0; i < objects.size(); i++) {
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(objects[i]->getModel()));
    glDrawArrays(GL_TRIANGLES, offset, objects[i]->getVerticesCount()/_VERTEX_INFO_SIZE);
    offset += objects[i]->getVerticesCount()/_VERTEX_INFO_SIZE;
  }

  //draw axis
  unsigned int colorLoc = glGetUniformLocation(_currentProgram->getProgramId(), "color");
  unsigned int colorSetLoc = glGetUniformLocation(_currentProgram->getProgramId(), "colorSet");
  glUniform4fv(colorLoc, 1, glm::value_ptr(glm::vec4(1.0f, 0.0f, 0.0f, 0.5f)));
  glUniform1i(colorSetLoc, 1);
	glDrawArrays(GL_LINES, offset, 2);
  glUniform4fv(colorLoc, 1, glm::value_ptr(glm::vec4(0.0f, 1.0f, 0.0f, 0.5f)));
  glDrawArrays(GL_LINES, offset+2, 2);
  glUniform4fv(colorLoc, 1, glm::value_ptr(glm::vec4(0.0f, 0.0f, 1.0f, 0.5f)));
  glDrawArrays(GL_LINES, offset+4, 2);
  glUniform1i(colorSetLoc, 0);

  // events
  glfwSwapBuffers(_windowId);
  glfwPollEvents();
}



// TODO draw grid
// if(glfwGetMouseButton(_windowId, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
//
//   // float camX = sin(glfwGetTime()) * radius;
//   // float camZ = cos(glfwGetTime()) * radius;
//   // glm::mat4 view;
//   // view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.
//   // get angles
//   double xPos, yPos;
//   glfwGetCursorPos(_windowId, &xPos, &yPos);
//   xPos -= _xPos;
//   yPos -= _yPos;
//   glm::vec3 horizontal = float(xPos) * glm::normalize(cameraRight);
//   glm::vec3 vertical = float(yPos) * glm::normalize(cameraUp);
//   glm::vec2 sum = glm::vec2(cameraPos.x + horizontal.x, cameraPos.z + horizontal.z);
//   glm::vec2 aaa = glm::vec2(cameraPos.x, cameraPos.z);
//   float angle = glm::angle(glm::normalize(aaa), glm::normalize(sum));
//   float radius = glm::length(cameraPos);
//   float camX = sin(angle) * radius;
//   float camZ = cos(angle) * radius;
//   std::cout << angle << std::endl;
//   std::cout << camX << ", " << camZ <<  std::endl;
//   // calculate vectors
//   cameraPos = glm::vec3(camX, 0.0f, camZ);
//
//   // update cameraPos and cameraRight
//   glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
//   glm::vec3 cameraDirection = glm::normalize(cameraPos);
//   cameraRight = glm::normalize(glm::cross(up, cameraDirection));
//   cameraUp = glm::cross(cameraDirection, cameraRight);
// } else {
//   glfwGetCursorPos(_windowId, &_xPos, &_yPos);
// }
