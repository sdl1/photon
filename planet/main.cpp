#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

#include "Photon.h"
#include "TerrainNode.h"

class Scene : public photon::Node
{
  public:
    Scene()
    {
      centrecube = new photon::shapes::Cube(0.25);
      light = new photon::shapes::Cube(0.5);
      light->setPosition(glm::vec3(5,5,2));

      auto f = [](glm::vec3 pos)
      {
        float x = pos[0];
        float y = pos[1];
        return sin(x)*cos(y);
      };
			terrain = new TerrainNode(10.0, f);

      addChild(this->centrecube);
      addChild(this->terrain);
      addChild(this->light);
    }

    photon::shapes::Cube *centrecube;
    TerrainNode *terrain;
    photon::shapes::Cube *light;
};

int main()
{

  photon::Photon photon;

  Scene scene;

  // Shaders
  photon::Shader defaultshader("../shaders/default.vert", "../shaders/default.frag");
  photon::Shader lightshader("../shaders/lightshader.vert", "../shaders/lightshader.frag");
  defaultshader.setUniform("light_color", glm::vec3(1,1,1));
  defaultshader.setUniform("light_pos", scene.light->getPosition());
  photon.setShader(0, defaultshader);
  photon.setShader(1, lightshader);
  scene.light->setShaderType(1);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glm::mat4 projection;
  projection = glm::perspective(glm::radians(45.0f), (GLfloat) photon.getWidth() / (GLfloat) photon.getHeight(), 0.1f, 100.0f);

  //glm::vec3 cameraPos(-1.0f, 1.0f, 5.0f);
  //glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
  glm::vec3 cameraPos(0.0f, 0.0f, 5.0f);
  glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
  photon::FPSCamera camera(cameraPos, cameraFront);

  // Capture and hide cursor
  glfwSetInputMode(photon.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetWindowUserPointer(photon.getWindow(), &camera);
  auto func = [](GLFWwindow* window, double xpos, double ypos)
  {
    static_cast<photon::FPSCamera*>(glfwGetWindowUserPointer(window))->mouse_callback(xpos, ypos);
  };
  glfwSetCursorPosCallback(photon.getWindow(), func);

  GLfloat time = glfwGetTime();
  GLfloat dt = 1.0;

  // Render to screen
  photon.setDefaultRenderTarget();
  while(!photon.shouldExit())
  {
    photon.pollEvents();
    photon.processInput();
    // Draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.processInput(photon.getWindow(), dt);
    glm::mat4 view = camera.getView();

    photon.Render(scene, view, projection);

    photon.swapBuffers();
    GLfloat newtime = glfwGetTime();
    dt = newtime - time;
    time = newtime;
  }

  return 0;
}
