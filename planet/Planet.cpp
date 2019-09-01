#include <GL/glew.h>

#include "Planet.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Planet::Planet(float L, std::function<float(glm::vec3)> height_fn) :
  L(L), height_fn(height_fn)
{
  // Top
  TerrainNode *child = new TerrainNode(L, height_fn);
  child->setPosition(glm::vec3(-L/2, -L/2, L/2));
  addChild(child);

  // Bottom
  child = new TerrainNode(L, height_fn);
  child->setRotation(glm::rotate(glm::mat4(), glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
  child->setPosition(glm::vec3(-L/2, +L/2, -L/2));
  addChild(child);

  // Right
  child = new TerrainNode(L, height_fn);
  child->setRotation(glm::rotate(glm::mat4(), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
  child->setPosition(glm::vec3(+L/2, -L/2, +L/2));
  addChild(child);

  // Left
  child = new TerrainNode(L, height_fn);
  child->setRotation(glm::rotate(glm::mat4(), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
  child->setPosition(glm::vec3(-L/2, -L/2, -L/2));
  addChild(child);

  // Front
  child = new TerrainNode(L, height_fn);
  child->setRotation(glm::rotate(glm::mat4(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
  child->setPosition(glm::vec3(-L/2, -L/2, -L/2));
  addChild(child);

  // Back
  child = new TerrainNode(L, height_fn);
  child->setRotation(glm::rotate(glm::mat4(), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
  child->setPosition(glm::vec3(-L/2, +L/2, +L/2));
  addChild(child);
}

Planet::~Planet()
{
}

void Planet::RenderMe()
{
}

void Planet::updateLOD(glm::vec3 pos, glm::vec3 front)
{
}

