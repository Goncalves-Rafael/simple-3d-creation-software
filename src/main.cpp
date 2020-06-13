#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "project.h"
#include "log.h"

int main (int argc, char* argv[]) {
  Log::init();
  SIMCS_LOG_TRACE("Initialized: {0}", "SIMCS");
  SIMCS_LOG_DEBUG("Initialized: {0}", "SIMCS");
  SIMCS_LOG_INFO("Initialized: {0}", "SIMCS");
  SIMCS_LOG_WARN("Initialized: {0}", "SIMCS");
  SIMCS_LOG_ERROR("Initialized: {0}", "SIMCS");
  SIMCS_LOG_CRITICAL("Initialized: {0}", "SIMCS");
  Project* project = new Project("name");
  project->run();
}
