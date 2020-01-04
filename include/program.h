#ifndef PROGRAM_H
#define PROGRAM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "shader.h"

class Program {
private:
  unsigned int programId;
  void setProgramId(unsigned int id);
  std::vector<Shader*> _shaders;

public:

  // unsigned int indices [6] = {
  //   0, 1, 2,
  //   1, 2, 3
  // };
  Program();

  unsigned int getProgramId();

  void use();
  void createVertexShader(const GLchar* shaderPath);
  void createFragmentShader(const GLchar* shaderPath);

  // FIXME right

  // TODO listShaders()
  // TODO removeShader()
  // TODO reorderShaders()
};

#endif
