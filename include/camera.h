#ifndef CAMERA_H
#define CAMERA_H

class Camera {
private:
  glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
  glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
  glm::mat3 rotationV = glm::mat3(1.0f);

public:
  Camera();

  void moveCameraRight();
  void moveCameraLeft();
  void moveCameraUp();
  void moveCameraDown();

  void turnCameraRight();
  void turnCameraLeft();
  void turnCameraUp();
  void turnCameraDown();
};

#endif

// float cameraSpeed = 0.05f; // adjust accordingly
// float angleSpeed = 0.015f;
// if (glfwGetKey(windowId, GLFW_KEY_W) == GLFW_PRESS)
//   cameraPos += cameraSpeed * cameraFront;
// if (glfwGetKey(windowId, GLFW_KEY_S) == GLFW_PRESS)
//   cameraPos -= cameraSpeed * cameraFront;
// if (glfwGetKey(windowId, GLFW_KEY_A) == GLFW_PRESS)
//   cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
// if (glfwGetKey(windowId, GLFW_KEY_D) == GLFW_PRESS)
//   cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
// if (glfwGetKey(windowId, GLFW_KEY_E) == GLFW_PRESS)
//   cameraFront += glm::normalize(glm::cross(cameraFront, cameraUp)) * angleSpeed;
// if (glfwGetKey(windowId, GLFW_KEY_Q) == GLFW_PRESS)
//   cameraFront -= glm::normalize(glm::cross(cameraFront, cameraUp)) * angleSpeed;
// if (glfwGetKey(windowId, GLFW_KEY_Z) == GLFW_PRESS) {
//   rotationV = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), glm::cross(cameraFront, cameraUp)));
//   cameraUp = rotationV * cameraUp;
//   cameraFront = rotationV * cameraFront;
//   // std::cout << "temp" << temp.x << ", "<< temp.y << ", " << temp.z << std::endl;
//   // std::cout << "up" << cameraUp.x << ", "<< cameraUp.y << ", " << cameraUp.z << std::endl;
//   // std::cout << "cameraFront" << cameraFront.x << ", "<< cameraFront.y << ", " << cameraFront.z << std::endl;
// }
// if (glfwGetKey(windowId, GLFW_KEY_X) == GLFW_PRESS) {
//   rotationV = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(-1.0f), glm::cross(cameraFront, cameraUp)));
//   cameraUp = rotationV * cameraUp;
//   cameraFront = rotationV * cameraFront;
// }


// float radius = 10.0f;
// float camX = sin(glfwGetTime()) * radius;
// float camZ = cos(glfwGetTime()) * radius;
// glm::mat4 view;
// view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
