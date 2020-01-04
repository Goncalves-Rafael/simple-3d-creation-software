#include "project.h"

Project::Project(std::string name) {
  _name = name;
  _renderer = new Renderer(1920, 1080);
  // createTexture("/home/rafael/Desktop/wall.jpg");
}
  // void createTexture(const GLchar* imgPath);
  // void processInput() {
  //
  // }
void Project::createCube() {
  _objects.push_back(new Object(_CUBE_VERTICES_, 180));
  _verticesCount += 180;
}

void Project::createTexture(const GLchar* imgPath) {
  _texture = new Texture(imgPath);
}

void Project::run() {
  _renderer->prepare();
  _renderer->sendData(_objects, _verticesCount);
  _renderer->draw(_objects);
  // _renderer.sendTexture(_texture);
}
