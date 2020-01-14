#include "object.h"

Object::Object(int numberOfVertices) {
  _vertices = new float[numberOfVertices]();
  _verticesCount = numberOfVertices;
}

Object::Object(const float *vertices, int size, float x, float y, float z) {
  _verticesCount = size;
  _vertices = new float[size]();
  for(int i = 0; i < size; i++) {
    _vertices[i] = vertices[i];
  }
  _model = glm::translate(_model, glm::vec3(x,y,z));
}

Object::Object(float *vertices, int size, float x, float y, float z) {
  _verticesCount = size;
  _vertices = new float[size]();
  for(int i = 0; i < size; i++) {
    _vertices[i] = vertices[i];
  }
  _model = glm::translate(_model, glm::vec3(x,y,z));
}


float* Object::getVertices() {
  return _vertices;
}

int Object::getVerticesCount() {
  return _verticesCount;
}

void Object::setModel(glm::mat4 matrix) {
  _model = matrix;
}

glm::mat4 Object::getModel() {
  return _model;
}

void Object::moveTo(glm::vec3 dest) {
  _model = glm::translate(glm::mat4(1.0f), dest);
}

Object::~Object() {
  delete(_vertices);
}
