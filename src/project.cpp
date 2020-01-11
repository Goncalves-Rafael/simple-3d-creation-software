#include "project.h"

Project::Project(std::string name) {
  _name = name;
  _renderer = new Renderer(1280, 720);
  // createTexture("/home/rafael/Desktop/wall.jpg");
}
  // void createTexture(const GLchar* imgPath);
  // void processInput() {
  //
  // }
void Project::createCube() {
  float x,y,z;
  std::cout << "Enter x:\n";
  std::cin >> x;
  std::cout << x;
  std::cout << "Enter y:\n";
  std::cin >> y;
  std::cout << y;
  std::cout << "Enter z:\n";
  std::cin >> z;
  std::cout << z;
  _objects.push_back(new Object(_CUBE_VERTICES_, 180, x, y, z));
  _verticesCount += 180;
  _renderer->sendData(_objects, _verticesCount);
  std::cin.clear();
  fflush(stdin);
}

void Project::createCube(float x, float y, float z) {
  _objects.push_back(new Object(_CUBE_VERTICES_, 180, x, y, z));
  _verticesCount += 180;
  _renderer->sendData(_objects, _verticesCount);
}

void Project::createTexture(const GLchar* imgPath) {
  _texture = new Texture(imgPath);
}

void Project::run() {
  _renderer->prepare();
  createCube(0.0f,0.0f,0.0f);
  createCube(1.0f,1.0f,1.0f);
  createCube(1.0f,1.0f,-1.0f);
  createCube(1.0f,-1.0f,1.0f);
  createCube(1.0f,-1.0f,-1.0f);
  createCube(-1.0f,1.0f,1.0f);
  createCube(-1.0f,1.0f,-1.0f);
  createCube(-1.0f,-1.0f,1.0f);
  createCube(-1.0f,-1.0f,-1.0f);
  createCube(2.0f,2.0f,2.0f);
  createCube(2.0f,2.0f,-2.0f);
  createCube(2.0f,-2.0f,2.0f);
  createCube(2.0f,-2.0f,-2.0f);
  createCube(-2.0f,2.0f,2.0f);
  createCube(-2.0f,2.0f,-2.0f);
  createCube(-2.0f,-2.0f,2.0f);
  createCube(-2.0f,-2.0f,-2.0f);
  createCube(0.0f,-2.0f,-2.0f);
  createCube(0.0f,-2.0f,2.0f);
  createCube(0.0f,2.0f,-2.0f);
  createCube(0.0f,2.0f,2.0f);
  createCube(2.0f,2.0f,0.0f);
  createCube(2.0f,-2.0f,0.0f);
  createCube(-2.0f,2.0f,0.0f);
  createCube(-2.0f,-2.0f,0.0f);
  while(!glfwWindowShouldClose(_renderer->getWindowId())) {
    processInput();
    _renderer->draw(_objects);
  }
  glfwTerminate();
  // _renderer.sendTexture(_texture);
}

void Project::processInput() {
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(_renderer->getWindowId(), true);
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_D) == GLFW_PRESS) {
    rotateCamera(1,0);
  }
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_A) == GLFW_PRESS) {
    rotateCamera(-1,0);
  }
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_W) == GLFW_PRESS) {
    rotateCamera(0,1);
  }
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_S) == GLFW_PRESS) {
    rotateCamera(0,-1);
  }
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_C) == GLFW_PRESS){
    createCube();
  }
  if(glfwGetMouseButton(_renderer->getWindowId(), GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
    double tempX, tempY;
    glm::vec2 tempDir;
    glfwGetCursorPos(_renderer->getWindowId(), &tempX, &tempY);
    tempX -= _mouseX;
    tempY -= _mouseY;
    if(tempX != 0 || tempY != 0) {
      tempDir = glm::vec2(tempX, tempY);
      if(glm::length(tempDir) > 1){
        rotateCamera(-tempX, -tempY);
      }
      tempDir = glm::normalize(tempDir);
      _mouseX += tempDir.x;
      _mouseY += tempDir.y;
    }
  } else {
    glfwGetCursorPos(_renderer->getWindowId(), &_mouseX, &_mouseY);
  }
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_Z) == GLFW_PRESS){
    zoomCamera(0.05f);
  }
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_X) == GLFW_PRESS){
    zoomCamera(-.05f);
  }
}

void Project::rotateCamera(float x, float y) {
  glm::mat3 viewTemp = glm::mat3(1.0f);
  float angleSpeed = 0.5f;
  if(x != 0) {
    viewTemp = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(angleSpeed), glm::normalize(x*_renderer->cameraUp)));
  }
  if(y != 0) {
    viewTemp *= glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(angleSpeed), glm::normalize(y*_renderer->cameraRight)));
  }

  _renderer->cameraPos = viewTemp * _renderer->cameraPos;
  _renderer->cameraRight = viewTemp * _renderer->cameraRight;
  _renderer->cameraUp = viewTemp * _renderer->cameraUp;
}

void Project::zoomCamera(float dist) {
  glm::mat4 desloc = glm::translate(glm::mat4(1.0f),dist*_renderer->cameraPos);
  _renderer->cameraPos = glm::vec3(desloc * glm::vec4(_renderer->cameraPos,1.0f));
}
