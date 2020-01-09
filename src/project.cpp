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
    glm::mat3 viewTemp;
    viewTemp = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), _renderer->cameraUp));
    _renderer->cameraPos = viewTemp * _renderer->cameraPos;
    _renderer->cameraRight = viewTemp * _renderer->cameraRight;
    _renderer->cameraUp = viewTemp * _renderer->cameraUp;
  }
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_A) == GLFW_PRESS) {
    glm::mat3 viewTemp;
    viewTemp = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), -_renderer->cameraUp));
    _renderer->cameraPos = viewTemp * _renderer->cameraPos;
    _renderer->cameraRight = viewTemp * _renderer->cameraRight;
    _renderer->cameraUp = viewTemp * _renderer->cameraUp;
  }
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_W) == GLFW_PRESS) {
    glm::mat3 viewTemp;
    viewTemp = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), -_renderer->cameraRight));
    _renderer->cameraPos = viewTemp * _renderer->cameraPos;
    _renderer->cameraRight = viewTemp * _renderer->cameraRight;
    _renderer->cameraUp = viewTemp * _renderer->cameraUp;
  }
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_S) == GLFW_PRESS) {
    glm::mat3 viewTemp;
    viewTemp = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), _renderer->cameraRight));
    _renderer->cameraPos = viewTemp * _renderer->cameraPos;
    _renderer->cameraRight = viewTemp * _renderer->cameraRight;
    _renderer->cameraUp = viewTemp * _renderer->cameraUp;
  }
  if(glfwGetKey(_renderer->getWindowId(), GLFW_KEY_C) == GLFW_PRESS){
    createCube();
  }
}
