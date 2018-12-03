#include "Photon.h"

#include <iostream>

namespace photon
{
  Photon::Photon() :
    width(1024), height(768)
  {
    if(!glfwInit())
    {
      std::cout << "Error initialising GLFW\n";
      // TODO throw
    }

    //glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old opengl
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // TODO window management, fullscreen, ...

    window = glfwCreateWindow(width, height, "Tutorial", nullptr, nullptr);
    if(window==nullptr)
    {
      std::cout << "Failed to open GLFW window\n";
      glfwTerminate();
      // TODO throw
    }
    glfwMakeContextCurrent(window);


    glewExperimental = true; // Needed in core profile
    if(glewInit() != GLEW_OK)
    {
      std::cout << "Failed to initialise GLEW\n";
      // TODO throw
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
  }

  Photon::~Photon()
  {
    glfwTerminate();
  }

  void Photon::processInput()
  {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, true);
    }
  }

  void Photon::pollEvents()
  {
    glfwPollEvents();
  }

  bool Photon::shouldExit()
  {
    return glfwWindowShouldClose(window);
  }

  void Photon::swapBuffers()
  {
    glfwSwapBuffers(window);
  }

  GLFWwindow* Photon::getWindow()
  {
    return window;
  }
  
  void Photon::setRenderTarget(photon::RenderTarget& target)
  {
    glBindFramebuffer(GL_FRAMEBUFFER, target.fbo); 
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
      std::cout << "Error binding framebuffer.\n";
      exit(1);
    }
  }
  
  void Photon::setDefaultRenderTarget()
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0); 
  }
}
