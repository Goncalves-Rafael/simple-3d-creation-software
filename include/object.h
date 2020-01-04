#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>

#include <iostream>

class Object {
private:
  float*    _vertices;
  int       _verticesCount;
  glm::mat4 _model      = glm::mat4(1.0f);

public:
  Object(int numberOfVertices);
  Object(const float *vertices, int size);
  Object(float *vertices, int size);

  float*    getVertices();
  int       getVerticesCount();
  void      setModel(glm::mat4 matrix);
  glm::mat4 getModel();

  ~Object();
};

#endif
