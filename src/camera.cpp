#include "camera.h"

Camera::Camera() {
  _cameraPos = glm::vec3(0.0f, 3.0f, -5.0f);
  _cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
  _cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);

  glm::vec3 cameraDirection = glm::normalize(_cameraPos);
  _cameraRight = glm::normalize(glm::cross(_cameraUp, cameraDirection));
  _cameraUp = glm::cross(cameraDirection, _cameraRight);
}

void Camera::rotateCameraAroundTarget(glm::vec2 rotateVector) {
  glm::mat3 viewTemp = glm::mat3(1.0f);
  float angleSpeed = 0.5f;
  std::cout << "rotX: " << rotateVector.x << ", " << "rotY: " <<  rotateVector.y << std::endl;
  if(rotateVector.x == 0 && rotateVector.y == 0) {
    return;
  }
  if (rotateVector.y != 0) {
    viewTemp = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(angleSpeed), glm::normalize(rotateVector.y * _cameraRight)));
  }

  if (rotateVector.x != 0) {
    viewTemp *= glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(angleSpeed), glm::normalize(glm::vec3(0.0f,_cameraUp.y *rotateVector.x,0.0f))));
  }


  _cameraPos = viewTemp * _cameraPos;
  _cameraRight = viewTemp * _cameraRight;
  _cameraUp = viewTemp * _cameraUp;
}

void Camera::zoomCamera(float dist) {
  glm::mat4 desloc = glm::translate(glm::mat4(1.0f),dist*_cameraPos);
  _cameraPos = glm::vec3(desloc * glm::vec4(_cameraPos,1.0f));
}

// void Camera::moveCamera

glm::mat4 Camera::getCameraView() {
  return glm::lookAt(_cameraPos, _cameraTarget - _cameraPos, _cameraUp);
}
