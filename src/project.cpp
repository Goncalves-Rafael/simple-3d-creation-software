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
    _baseCam->rotateCameraAroundTarget(glm::vec2(1,0));
  }
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_A) == GLFW_PRESS) {
    _baseCam->rotateCameraAroundTarget(glm::vec2(-1,0));
  }
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_W) == GLFW_PRESS) {
    _baseCam->rotateCameraAroundTarget(glm::vec2(0,1));
  }
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_S) == GLFW_PRESS) {
    _baseCam->rotateCameraAroundTarget(glm::vec2(0,-1));
  }
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_C) == GLFW_PRESS){
    createCube();
  }
  if(glfwGetMouseButton(_renderer->getWindowId(), GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
    glm::vec2 tempDir = getCursorDisplacement();
    // std::cout << tempDir.x << ", " << tempDir.y << std::endl;
    if (abs(tempDir.y) < 2) tempDir.y = 0;
    if (abs(tempDir.x) < 2) tempDir.x = 0;
    if(tempDir.x != 0 || tempDir.y != 0) {
      if(glm::length(tempDir) > 1){
        if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
          _baseCam->moveCamera(tempDir);
        } else {
          _baseCam->rotateCameraAroundTarget(-tempDir);
        }
      }
    }
  } else if (glfwGetKey(_renderer->getWindowId(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    glm::vec2 tempDir = glm::normalize(getCursorDisplacement());
    float length = glm::length(tempDir);
    // std::cout << tempDir.x << ", " << tempDir.y << std::endl;
    if(tempDir.x > 0) {
      _baseCam->zoomCamera(length*0.01);
    } else if (tempDir.x < 0) {
      _baseCam->zoomCamera(-length*0.01);
    }
  } else {
    glfwGetCursorPos(_renderer->getWindowId(), &_mouseX, &_mouseY);
  }
  // if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_Z) == GLFW_PRESS){
  //   zoomCamera(0.05f);
  // }
  // if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_X) == GLFW_PRESS){
  //   zoomCamera(-.05f);
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
  glm::vec2 direction;

  glfwGetCursorPos(_renderer->getWindowId(), &tempX, &tempY);
  tempX -= _mouseX;
  tempY -= _mouseY;
  direction = glm::vec2(tempX, tempY);
  // std::cout << "tempX: " << tempX << ", " << "tempY: " <<  tempY << std::endl;
  length = glm::length(tempY);
  if(length > 0) {
    _mouseX += direction.x/length;
    _mouseY += direction.y/length;
  }

  return direction;
}
