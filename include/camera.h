#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/projection.hpp>

class Camera {
private:
  glm::vec3 _cameraPos;
  glm::vec3 _cameraUp;
  glm::vec3 _cameraRight;
  glm::vec3 _cameraTarget;
  
  float _cameraRotationSpeed;
  float _cameraZoomSpeed;
  float _cameraPanSpeed;

public:
  Camera();

  void rotateCameraAroundTarget(glm::vec2 rotateVector, float deltaSeconds);
  void zoomCamera(float dist, float deltaSeconds);
  void moveCamera(glm::vec2 dirVector, float deltaSeconds);
  glm::mat4 getCameraView();
};

#endif
