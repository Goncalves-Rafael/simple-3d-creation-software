#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "project.h"

int main (int argc, char* argv[]) {
  Project* project = new Project("name");
  project->createCube();
  project->run();
}
