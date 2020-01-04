#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader {
private:
  // the program ID
  unsigned int shaderId;
  GLenum shaderType;
  const char* shaderCode;

  void setShaderId(unsigned int id);
  void setShaderType(GLenum type);
  void setShaderCode(const char* newCode);

public:
  Shader(const GLchar* shaderPath, GLenum shaderType);

  unsigned int getShaderId();
  GLenum getShaderType();
  const char* getShaderCode();

  std::string getFileContent(const GLchar* shaderPath);
  unsigned int compileShader(const char* shaderCode, GLenum shaderType);
  // use/activate the shader
  // void use();
  // utility uniform functions
  // void setBool(const std::string &name, bool value) const;
  // void setInt(const std::string &name, int value) const;
  // void setFloat(const std::string &name, float value) const;
};

#endif
