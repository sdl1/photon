#ifndef PHOTON_H
#define PHOTON_H

#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Mesh.h"
#include "BasicShapes.h"
#include "Node.h"
#include "FPSCamera.h"
#include "RenderTarget.h"

namespace photon
{

  class Photon
  {
    public:
      Photon();
      ~Photon();
      void pollEvents();
      void processInput();
      int getWidth(){ return width; };
      int getHeight(){ return height; };
      bool shouldExit();
      void swapBuffers();
      GLFWwindow* getWindow();
      void setRenderTarget(photon::RenderTarget&);
      void setDefaultRenderTarget();

      void setShader(unsigned int shaderType, Shader shader);
      Shader& getShader(unsigned int shaderType) { return shaderMap[shaderType]; };

      virtual void Render(Node &node, glm::mat4 view, glm::mat4 projection, glm::mat4 model = glm::mat4());

    private:
      int width;
      int height;
      GLFWwindow *window;
      std::map<unsigned int, Shader> shaderMap;

      bool wireframe;
      void pressKey(int);
      void processKeys();
      std::map<int, bool> keydown;
  };

}

#endif
