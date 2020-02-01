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
  float angleSpeed = 0.85f;
  std::cout << "rotX: " << rotateVector.x << ", " << "rotY: " <<  rotateVector.y << std::endl;
  if(rotateVector.x == 0 && rotateVector.y == 0) {
    return;
  }
  glm::vec3 axis = (rotateVector.y * _cameraRight) + glm::vec3(0.0f,_cameraUp.y *rotateVector.x,0.0f);
  viewTemp = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(angleSpeed), glm::normalize(axis)));

  _cameraPos = viewTemp * _cameraPos;
  _cameraRight = viewTemp * _cameraRight;
  _cameraUp = viewTemp * _cameraUp;
}

void Camera::zoomCamera(float dist) {
  glm::mat4 desloc = glm::translate(glm::mat4(1.0f),dist*_cameraPos);
  _cameraPos = glm::vec3(desloc * glm::vec4(_cameraPos,1.0f));
}

void Camera::moveCamera(glm::vec2 dirVector) {
  float movSpeed = 0.005f;
  glm::vec3 projectedDir = dirVector.x*(glm::normalize(_cameraRight)) - dirVector.y*(glm::normalize(_cameraUp));
  _cameraPos.x += movSpeed*projectedDir.x;
  // std::cout << "dir: " << dirVector.x << ", " << dirVector.y << std::endl;
  projectedDir = -glm::proj(projectedDir, glm::vec3(1,0,0)) - glm::proj(projectedDir, glm::vec3(0,0,1));
  _cameraTarget += movSpeed*projectedDir;
  std::cout << "_cameraTarget: " << _cameraTarget.x << ", " << _cameraTarget.y << ", " << _cameraTarget.z << std::endl;
  // std::cout << "_cameraPos: " << _cameraPos.x << ", " << _cameraPos.y << ", " << _cameraPos.z << std::endl;
}

glm::mat4 Camera::getCameraView() {
  return glm::lookAt(_cameraPos, _cameraTarget, _cameraUp);
}
