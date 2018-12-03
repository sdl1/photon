#include "FPSCamera.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace photon
{
  FPSCamera::FPSCamera(glm::vec3 cameraPos, glm::vec3 cameraFront) :
    cameraPos(cameraPos), cameraFront(cameraFront), cameraSpeed(2.0), firstMouse(true)
  {
    this->setCoords();
  }

  void FPSCamera::setCoords()
  {
    cameraZ = glm::normalize(cameraPos - cameraFront);
    glm::vec3 up(0.0f, 1.0f, 0.0f);
    cameraRight = glm::normalize(glm::cross(up, cameraZ));
    cameraUp = glm::cross(cameraZ, cameraRight);
  }

  glm::mat4 FPSCamera::getView()
  {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
  }

  void FPSCamera::processInput(GLFWwindow *window, GLfloat dt)
  {
    GLfloat speed = cameraSpeed * dt;
    // TODO event listener
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
      cameraPos += speed*cameraFront;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
      cameraPos -= speed*cameraFront;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
      cameraPos -= speed*cameraRight;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
      cameraPos += speed*cameraRight;
    }
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
      cameraPos += speed*cameraUp;
    }
    if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
      cameraPos -= speed*cameraUp;
    }
  }
  
  void FPSCamera::mouse_callback(double xpos, double ypos)
  {
    if(firstMouse)
    {
      this->xpos = xpos;
      this->ypos = ypos;
      firstMouse = false;
      return;
    }
    double sensitivity = 0.001;
    double dx = sensitivity*(xpos - this->xpos);
    double dy = sensitivity*(ypos - this->ypos);

    // Move mouse right -> rotate right
    float angle = -dx;
    // TODO need to re-normalise??
    cameraZ = glm::rotate(cameraZ, angle, cameraUp);
    cameraFront = glm::rotate(cameraFront, angle, cameraUp);
    cameraRight = glm::rotate(cameraRight, angle, cameraUp);
    angle = -dy;
    cameraFront = glm::rotate(cameraFront, angle, cameraRight);
    cameraUp = glm::rotate(cameraUp, angle, cameraRight);
    cameraZ = glm::rotate(cameraZ, angle, cameraRight);
    //cameraRight = glm::rotate(cameraRight, angle, cameraUp);

    this->xpos = xpos;
    this->ypos = ypos;
  }
}
