#include "camera.h"
#include <GLFW/glfw3.h>

Camera::Camera() {
  _cameraPos = glm::vec3(0.0f, 0.0f, -5.0f);
  _cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
  _cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);
  _cameraRotationSpeed = 1000.f;
  _cameraZoomSpeed = 5.f;
  _cameraPanSpeed = 40.f;

  glm::vec3 cameraDirection = glm::normalize(_cameraPos);
  _cameraRight = glm::normalize(glm::cross(_cameraUp, cameraDirection));
  _cameraUp = glm::cross(cameraDirection, _cameraRight);
}

void Camera::rotateCameraAroundTarget(glm::vec2 rotateVector, float deltaSeconds) {
  glm::mat4 viewDesloc = glm::mat4(1.0f);
  glm::mat3 viewTemp;
  float angleSpeed = _cameraRotationSpeed * deltaSeconds;
  
  if(rotateVector.x == 0 && rotateVector.y == 0) {
    return;
  }
  glm::vec3 axis = (rotateVector.y * _cameraRight) + glm::vec3(0.0f,_cameraUp.y *rotateVector.x,0.0f);
  viewTemp = glm::mat3(glm::rotate(viewDesloc, glm::radians(angleSpeed), axis));
  _cameraPos -= _cameraTarget;
  _cameraPos = viewTemp * _cameraPos;
  _cameraPos += _cameraTarget;
  _cameraRight = viewTemp * _cameraRight;
  _cameraUp = viewTemp * _cameraUp;
}

void Camera::zoomCamera(float dist, float deltaSeconds) { 
  _cameraPos -= _cameraTarget;
  glm::mat4 desloc = glm::translate(glm::mat4(1.0f), deltaSeconds * _cameraZoomSpeed * dist * _cameraPos);
  _cameraPos = glm::vec3(desloc * glm::vec4(_cameraPos, 1.0f));
  _cameraPos += _cameraTarget;
}

void Camera::moveCamera(glm::vec2 dirVector, float deltaSeconds) {
  dirVector = glm::normalize(dirVector);
  glm::vec3 projectedDir = dirVector.x * glm::normalize(_cameraRight) - dirVector.y * (_cameraUp);
  _cameraPos += deltaSeconds * _cameraPanSpeed * projectedDir;
  _cameraTarget += deltaSeconds * _cameraPanSpeed * projectedDir;
}

glm::mat4 Camera::getCameraView() {
  return glm::lookAt(_cameraPos, _cameraTarget, _cameraUp);
}
