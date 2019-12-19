#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "shader.h"

shader::Shader(const GLchar* shaderPath, GLenum shaderType) {
  std::string shaderCode;
  std::ifstream shaderFile;
  // ensure ifstream objects can throw exceptions:
  shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  try {
    // open files
    shaderFile.open(shaderPath);
    std::stringstream shaderStream;
    // read file's buffer contents into streams
    shaderStream << shaderFile.rdbuf();
    // close file handlers
    shaderFile.close();
    // convert stream into string
    shaderCode   = shaderStream.str();
  } catch(std::ifstream::failure e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }
  const char* finalShaderCode = shaderCode.c_str();
  this.setShaderType(shaderType);
  this.setShaderId(this.compileShader(finalShaderCode, shaderType));
}

unsigned int shader::compileShader(const char* shaderCode, GLenum shaderType) {
  unsigned int shader;
  int success;
  char infoLog[521];

  shader = glCreateShader(shaderType);
  glShaderSource(shader, &shaderCode, NULL);

  glGetshaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 521, NULL, infoLog);
    std::cout << "ERROR::SHADER:: " << shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
}

unsigned int shader::getShaderId() {
  return this.shaderId;
}

void shader::setShaderId(unsigned int id) {
  this.shaderId = id;
}

GLenum shader::getShaderType() {
  return this.shaderType;
}

void shader::setShaderType(GLenum type) {
  this.shaderType = type;
}

// void ~shader::Shader() {
//
// }
