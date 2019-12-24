#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "program.h"

int main (int argc, char* argv[]) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  const char* vertex = "src/shaders/baseVertexShader.vs";
  const char* fragment = "src/shaders/baseFragmentShader.fs";
  Program *program = new Program();

  program->createVertexShader(vertex);
  program->createFragmentShader(fragment);

  program->use();
}
