#ifndef PROGRAM_H
#define PROGRAM_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <iterator>

#include "shader.h"


class Program {
private:
  unsigned int programId;
  std::vector<Shader*> shaders;
  GLFWwindow* windowId;

  void setProgramId(int id);
  static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
  unsigned int VBO, VAO;
  float vertices[18] = {
    -0.5f, +0.5f, 0.0f, 1.f, 0.0f, 0.0f,
     0.5f, +0.5f, 0.0f, 0.0f, 1.f, 0.0f,
     0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.f
  };
  Program();

  void use();
  void createVertexShader(const GLchar* shaderPath);
  void createFragmentShader(const GLchar* shaderPath);

  // FIXME right

  // TODO listShaders()
  // TODO removeShader()
  // TODO reorderShaders()
};

#endif
