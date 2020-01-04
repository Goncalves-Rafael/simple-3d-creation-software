#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "shader.h"

Shader::Shader(const GLchar* shaderPath, GLenum shaderType) {
  std::string shaderCode;
  std::ifstream shaderFile;

  try {
    shaderCode = getFileContent(shaderPath);
    const char* finalShaderCode = shaderCode.c_str();
    setShaderType(shaderType);
    setShaderCode(finalShaderCode);
    setShaderId(compileShader(finalShaderCode, shaderType));
  } catch(std::ifstream::failure e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }
}

std::string Shader::getFileContent(const GLchar* shaderPath) {
  std::ifstream shaderFile;
  shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  // open files
  shaderFile.open(shaderPath);
  std::stringstream shaderStream;
  // read file's buffer contents into streams
  shaderStream << shaderFile.rdbuf();
  // close file handlers
  shaderFile.close();
  // convert stream into string
  return shaderStream.str();
}

unsigned int Shader::compileShader(const char* shaderCode, GLenum shaderType) {
  unsigned int shader;
  int success;
  char infoLog[521];

  shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &shaderCode, NULL);
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 521, NULL, infoLog);
    std::cout << "ERROR::SHADER:: " << shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    return 0;
  }

  return shader;
}

unsigned int Shader::getShaderId() {
  return shaderId;
}

void Shader::setShaderId(unsigned int id) {
  shaderId = id;
}

GLenum Shader::getShaderType() {
  return shaderType;
}

void Shader::setShaderType(GLenum type) {
  shaderType = type;
}

void Shader::setShaderCode(const char* newCode) {
  shaderCode = newCode;
}

const char* Shader::getShaderCode() {
  return shaderCode;
}

// TODO void ~shader::Shader() {
//
// }
