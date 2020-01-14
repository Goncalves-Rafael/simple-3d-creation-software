#ifndef RENDERER_H
#define RENDERER_H

#define _VERTEX_INFO_SIZE 5

#include <glad/glad.h> // include glad to get all the required OpenGL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <vector>
#include <exception>


#include "program.h"
#include "object.h"

class Renderer {
private:
  unsigned int _VBO, _VAO, _EBO, _state;
  unsigned int _axisVBO;
  int _width, _height;
  GLFWwindow*  _windowId;
  Program*     _currentProgram;

  glm::mat4 _model      = glm::mat4(1.0f);
  glm::mat4 _view       = glm::mat4(1.0f);
  glm::mat4 _projection = glm::mat4(1.0f);
  double _xPos, _yPos;

  void static framebuffer_size_callback(GLFWwindow* window, int width, int height);

  void updateProjectionMatrix();
  void updateViewMatrix();
  void processInput();
  void sendAxisData(int offset);

public:

  Renderer();
  Renderer(int width, int height);

  int  prepare();
  int  sendData(std::vector<Object*> &objects, int verticesCount);
  GLFWwindow* getWindowId();
  void setProgram(Program* program);
  void draw(std::vector<Object*> &objects);
  void setView(glm::mat4 viewMatrix);

  // void (*newObj)();
};

#endif
