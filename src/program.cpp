
#include "program.h"

Program::Program() {
  programId = glCreateProgram();
}

void Program::createVertexShader(const GLchar* shaderPath) {
  _shaders.push_back(new Shader(shaderPath, GL_VERTEX_SHADER));
}

void Program::createFragmentShader(const GLchar* shaderPath) {
  _shaders.push_back(new Shader(shaderPath, GL_FRAGMENT_SHADER));
}

unsigned int Program::getProgramId() {
  return programId;
}
void Program::linkShaders() {
  int success;
  char *infoLog;
  glAttachShader(programId, _shaders[0]->getShaderId());
  glAttachShader(programId, _shaders[1]->getShaderId());
  glLinkProgram(programId);
  glGetProgramiv(programId, GL_LINK_STATUS, &success);
  if(!success) {
      glGetProgramInfoLog(programId, 512, NULL, infoLog);
      std::cout << "ERROR::PROGRAM::SHADER::LINK_FAILED\n" << infoLog << std::endl;
  }
  // glDeleteShader(_shaders[0]->getShaderId());
  // glDeleteShader(_shaders[1]->getShaderId());
}
void Program::setAttributes() {
  //Attributes config
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(GL_FLOAT)));
  glEnableVertexAttribArray(1);
  glEnable(GL_DEPTH_TEST);
  // glBindVertexArray(0);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode
}
