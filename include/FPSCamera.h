#ifndef FPSCAMERA_H
#define FPSCAMERA_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace photon
{
  class FPSCamera
  {
    public:
      // Pos, front in world space
      FPSCamera(glm::vec3 cameraPos, glm::vec3 cameraFront);
      glm::mat4 getView();
      void processInput(GLFWwindow* window, GLfloat dt);
      void mouse_callback(double xpos, double ypos);

    private:
      void setCoords();
      glm::vec3 cameraPos;
      glm::vec3 cameraFront;

      glm::vec3 cameraZ;
      glm::vec3 cameraRight;
      glm::vec3 cameraUp;

      float cameraSpeed;
      bool firstMouse;
      double xpos, ypos;
  };
}


#endif
