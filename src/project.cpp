#include "project.h"

Project::Project(std::string name) {
  _name = name;
  _renderer = new Renderer(1280, 720);
  _baseCam = new Camera();
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

void Project::createArrow(float x, float y, float z) {
  _objects.push_back(new Object(_ARROW_VERTICES_, 180, x, y, z));
  _verticesCount += 180;
  _renderer->sendData(_objects, _verticesCount);
}

void Project::createTexture(const GLchar* imgPath) {
  _texture = new Texture(imgPath);
}

void Project::run() {
  _renderer->prepare();
  createArrow(0.0f,0.0f,0.0f);
  createCube(1.0f,0.0f,1.0f);
  // createCube(1.0f,1.0f,-1.0f);
  // createCube(1.0f,-1.0f,1.0f);
  // createCube(1.0f,-1.0f,-1.0f);
  // createCube(-1.0f,1.0f,1.0f);
  // createCube(-1.0f,1.0f,-1.0f);
  // createCube(-1.0f,-1.0f,1.0f);
  // createCube(-1.0f,-1.0f,-1.0f);
  // createCube(2.0f,2.0f,2.0f);
  // createCube(2.0f,2.0f,-2.0f);
  // createCube(2.0f,-2.0f,2.0f);
  // createCube(2.0f,-2.0f,-2.0f);
  // createCube(-2.0f,2.0f,2.0f);
  // createCube(-2.0f,2.0f,-2.0f);
  // createCube(-2.0f,-2.0f,2.0f);
  // createCube(-2.0f,-2.0f,-2.0f);
  // createCube(0.0f,-2.0f,-2.0f);
  // createCube(0.0f,-2.0f,2.0f);
  // createCube(0.0f,2.0f,-2.0f);
  // createCube(0.0f,2.0f,2.0f);
  // createCube(2.0f,2.0f,0.0f);
  // createCube(2.0f,-2.0f,0.0f);
  // createCube(-2.0f,2.0f,0.0f);
  // createCube(-2.0f,-2.0f,0.0f);
  float time = (float)glfwGetTime();
  lastTimeFrame = time;
  while(!glfwWindowShouldClose(_renderer->getWindowId())) {
    time = (float)glfwGetTime();
    _deltaSeconds = time - lastTimeFrame;
    lastTimeFrame = time;
    processInput();
    _renderer->setView(_baseCam->getCameraView());
    _renderer->draw(_objects);
  }
  glfwTerminate();
  // _renderer.sendTexture(_texture);
}

void Project::processInput() {
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(_renderer->getWindowId(), true);
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_D) == GLFW_PRESS) {
    _baseCam->rotateCameraAroundTarget(glm::vec2(1,0), _deltaSeconds);
  }
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_A) == GLFW_PRESS) {
    _baseCam->rotateCameraAroundTarget(glm::vec2(-1,0), _deltaSeconds);
  }
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_W) == GLFW_PRESS) {
    _baseCam->rotateCameraAroundTarget(glm::vec2(0,1), _deltaSeconds);
  }
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_S) == GLFW_PRESS) {
    _baseCam->rotateCameraAroundTarget(glm::vec2(0,-1), _deltaSeconds);
  }
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_C) == GLFW_PRESS){
    createCube();
  }
  if(glfwGetMouseButton(_renderer->getWindowId(), GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
    glm::vec2 tempDir = getCursorDisplacement() / _deltaSeconds;
    
    if(tempDir.x != 0 || tempDir.y != 0) {
      if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        _baseCam->moveCamera(tempDir, _deltaSeconds);
      } else {
        _baseCam->rotateCameraAroundTarget(-tempDir, _deltaSeconds);
      }
    }
  } else if (glfwGetKey(_renderer->getWindowId(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    glm::vec2 tempDir = glm::normalize(getCursorDisplacement());
    if (glm::abs(tempDir.x) > 0) {
      _baseCam->zoomCamera(tempDir.x, _deltaSeconds);
    }
  } else {
    glfwGetCursorPos(_renderer->getWindowId(), &_mouseX, &_mouseY);
  }
  // if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_Z) == GLFW_PRESS){
  //    _baseCam->zoomCamera(0.05f);
  // }
  // if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_X) == GLFW_PRESS){
  //    _baseCam->zoomCamera(-.05f);
  // }
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_F) == GLFW_PRESS){
    move();
  }
}

void Project::move() {
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
  _objects[0]->moveTo(glm::vec3(x,y,z));
}


glm::vec2 Project::getCursorDisplacement() {
  double tempX, tempY;
  float length;
  float mouseSpeed = 2000000.f;
  glm::vec2 direction;

  glfwGetCursorPos(_renderer->getWindowId(), &tempX, &tempY);
  tempX = tempX - _mouseX;
  tempY = tempY - _mouseY;
  if (glm::abs(tempX) < 5 && glm::abs(tempY) < 5) return glm::vec2(0, 0);
  
  direction = glm::vec2(tempX, tempY);
  length = glm::length(direction);
  if(length > 0) {
    _mouseX += direction.x;
    _mouseY += direction.y;
  }
  
  return direction;
}
