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

public:
  Camera();

  void rotateCameraAroundTarget(glm::vec2 rotateVector);
  void zoomCamera(float dist);
  void moveCamera(glm::vec2 dirVector);
  glm::mat4 getCameraView();
};

#endif
