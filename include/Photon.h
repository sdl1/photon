#ifndef PHOTON_H
#define PHOTON_H

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

    private:
      int width;
      int height;
      GLFWwindow *window;
  };

}

#endif
