#ifndef RENDERER_H
#define RENDERER_H

#define _VERTEX_INFO_SIZE 5

#include <glad/glad.h> // include glad to get all the required OpenGL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <vector>
#include <exception>


#include "program.h"
#include "object.h"

class Renderer {
private:
  unsigned int _VBO, _VAO, _EBO, _state;
  int _width, _height;
  GLFWwindow*  _windowId;
  Program*     _currentProgram;

  glm::mat4 _model      = glm::mat4(1.0f);
  glm::mat4 _view       = glm::mat4(1.0f);
  glm::mat4 _projection = glm::mat4(1.0f);

  void static framebuffer_size_callback(GLFWwindow* window, int width, int height);

  void updateProjectionMatrix();
  void updateViewMatrix();
  void processInput();

public:
  Renderer();
  Renderer(int width, int height);

  int  prepare();
  int  sendData(std::vector<Object*> &objects, int verticesCount);
  void setProgram(Program* program);
  void draw(std::vector<Object*> &objects);

};

#endif
