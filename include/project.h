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
#include "renderer.h"

class Project {
private:
  std::string _name;
  int _width, _height, _verticesCount = 0;
  std::vector<Object*> _objects;
  Texture* _texture;
  Renderer* _renderer;

public:
  Project(std::string name);
  void createTexture(const GLchar* imgPath);
  void processInput();
  void createCube();
  void createCube(float x, float y, float z);
  void run();
};

#endif
