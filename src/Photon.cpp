#include "Photon.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

namespace photon
{
  Photon::Photon() :
    width(1024), height(768), wireframe(false)
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

  void Photon::pressKey(int key)
  {
    switch(key)
    {
      case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, true);
        break;
      case GLFW_KEY_L:
        //TODO proper logging
        std::cout << "Toggle wireframe\n";
        wireframe = !wireframe;
        if(wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
      case GLFW_KEY_R:
        std::cout << "Reload shaders\n";
        reloadShaders();
        break;
    }
  }

  void Photon::processKeys()
  {
    for(int key=GLFW_KEY_SPACE ; key<=GLFW_KEY_LAST ; key++)
    {
      if(glfwGetKey(window, key) == GLFW_PRESS && !keydown[key])
      {
        keydown[key] = true;
        pressKey(key);
      }
      if(glfwGetKey(window, key) == GLFW_RELEASE)
      {
        keydown[key] = false;
      }
    }

  }

  void Photon::processInput()
  {
    processKeys();
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

  void Photon::setShader(unsigned int shaderType, Shader shader)
  {
    shaderMap[shaderType] = shader;
  }

  // If model not specified, identity is default
  void Photon::Render(Node &node, glm::mat4 view, glm::mat4 projection, glm::mat4 model)
  {
    // TODO only do below once for each shader
    Shader shader = shaderMap[node.shaderType];
    shader.setUniform("view", view);
    shader.setUniform("projection", projection);
    shader.use();

    model = glm::translate(model, node.position);
    shader.setUniform("model", model);
    node.RenderMe();
    for(auto const & child : node.nodeList)
    {
      Render(*child, view, projection, model); 
    }
  }

  void Photon::reloadShaders()
  {
    for(auto & it : shaderMap)
    {
      it.second.reload();
    }
  }

}
