#include "object.h"

Object::Object(int numberOfVertices) {
  _vertices = new float[numberOfVertices]();
  _verticesCount = numberOfVertices;
}

Object::Object(const float *vertices, int size) {
  _verticesCount = size;
  _vertices = new float[size]();
  for(int i = 0; i < size; i++) {
    _vertices[i] = vertices[i];
  }
}

Object::Object(float *vertices, int size) {
  _verticesCount = size;
  _vertices = new float[size]();
  for(int i = 0; i < size; i++) {
    _vertices[i] = vertices[i];
  }
}


float* Object::getVertices() {
  return _vertices;
}

int Object::getVerticesCount() {
  return _verticesCount;
}

void Object::setModel(glm::mat4 matrix){
  _model = matrix;
}

glm::mat4 Object::getModel(){
  return _model;
}

Object::~Object() {
  delete(_vertices);
}
