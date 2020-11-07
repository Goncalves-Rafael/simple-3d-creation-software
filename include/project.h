#ifndef PROJECT_H
#define PROJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>

#include "texture.h"
#include "object.h"
#include "cube.h"
#include "arrow.h"
#include "camera.h"
#include "renderer.h"

class Project {
private:
  std::vector<Object*> _objects;
  Texture* _texture;
  Renderer* _renderer;
  Camera* _baseCam;
  std::string _name;
  int _width, _height, _verticesCount = 0;
  double _mouseX = 0, _mouseY = 0;
  float lastTimeFrame = 0.f;
  float _deltaSeconds = 0.f;

public:
  Project(std::string name);
  void createTexture(const GLchar* imgPath);
  void processInput();
  void createCube();
  void createCube(float x, float y, float z);
  void createArrow(float x, float y, float z);
  void move();
  void run();
  glm::vec2 getCursorDisplacement();
};

#endif
