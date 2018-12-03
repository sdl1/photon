#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//using namespace glm;

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

#include "Photon.h"

class Scene : public photon::Node
{
  public:
    Scene() :
      cubeshader("test/shader.vert", "test/shader.frag"),
      lightshader("test/lightshader.vert", "test/lightshader.frag")
    {
			ground = new photon::shapes::Square(10.0, glm::vec3(1,0,0));
      light = new photon::shapes::Cube(0.5);
      light->setPosition(glm::vec3(-1,2,0.5));
      cube = new photon::shapes::Cube(1.0, glm::vec3(0,0,1));
      cube->setPosition(glm::vec3(0.0, 0.5, 0.0));

      //photon::Shader cubeshader("test/shader.vert", "test/shader.frag");
      //photon::Shader lightshader("test/lightshader.vert", "test/lightshader.frag");
      //this->light->setShader(lightshader);
      //this->cube->setShader(cubeshader);
      cubeshader.setUniform("light_color", glm::vec3(1,1,1));
      cubeshader.setUniform("light_pos", light->getPosition());

      addChild(this->ground);
      addChild(this->light);
      addChild(this->cube);
    }

    void Draw(glm::mat4 view, glm::mat4 projection)
    {
      lightshader.setUniform("view", view);
      lightshader.setUniform("projection", projection);
      ground->Render(lightshader);
      light->Render(lightshader);
      cubeshader.setUniform("view", view);
      cubeshader.setUniform("projection", projection);
      cube->Render(cubeshader);
    }

  private:
    photon::shapes::Square *ground;
    photon::shapes::Cube *light;
    photon::shapes::Cube *cube;
    photon::Shader cubeshader;
    photon::Shader lightshader;
};

int main()
{

  photon::Photon photon;

  Scene scene;

//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glm::mat4 projection;
  projection = glm::perspective(glm::radians(45.0f), (GLfloat) photon.getWidth() / (GLfloat) photon.getHeight(), 0.1f, 100.0f);

  glm::vec3 cameraPos(-1.0f, 1.0f, 5.0f);
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

  // Render to image
  photon::RenderTargetImage image("tester.bmp");
  glm::mat4 view = camera.getView();
  photon.setRenderTarget(image);
  scene.Draw(view, projection);

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

    scene.Draw(view, projection);

    photon.swapBuffers();
    GLfloat newtime = glfwGetTime();
    dt = newtime - time;
    time = newtime;
  }

  return 0;
}
