#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//using namespace glm;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

#include "Photon.h"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
  if(key==GLFW_KEY_ESCAPE && action==GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

int main()
{
  if(!glfwInit())
  {
    std::cout << "Error initialising GLFW\n";
    return -1;
  }

  //glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old opengl
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow *window = glfwCreateWindow(1024, 768, "Tutorial", nullptr, nullptr);
  if(window==nullptr)
  {
    std::cout << "Failed to open GLFW window\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);


  glewExperimental = true; // Needed in core profile
  if(glewInit() != GLEW_OK)
  {
    std::cout << "Failed to initialise GLEW\n";
    return -1;
  }

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  glfwSetKeyCallback(window, key_callback);

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  photon::shapes::Cube cube(1.0f);

  photon::Shader shader("test/shader.vert", "test/shader.frag");

//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


  glm::mat4 projection;
  projection = glm::perspective(glm::radians(45.0f), (GLfloat) width / (GLfloat)height, 0.1f, 100.0f);
  shader.setUniform("projection", projection);

  while(!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    // Draw
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();

    GLfloat timeValue = glfwGetTime();
    //GLfloat offset = (sin(timeValue) / 2) + 0.5;
    GLfloat offset = timeValue * 50;
    //shader.setUniform("offset", offset);

    glm::mat4 model;
    //model = glm::rotate(model, glm::radians(offset), glm::vec3(0, 0, 1));
    model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(1, 0, 0));
    shader.setUniform("model", model);

    glm::mat4 view;
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -offset/100));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    //std::cout << glm::to_string(view) << "\n";
    shader.setUniform("view", view);

    //glm::mat4 tmp = projection * view * model;
    //std::cout << glm::to_string(tmp) << "\n";

    //TODO scene root, camera transform per node etc
    cube.Render();

    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}
