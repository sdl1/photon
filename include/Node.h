#ifndef NODE_H
#define NODE_H

#include <list>
#include <memory>
#include <glm/glm.hpp>

#include "Shader.h"

namespace photon
{
  class Node
  {
    friend class Photon;

    public:
      Node();
      virtual ~Node();
      void addChild(Node *node);
      void setPosition(glm::vec3 pos){ this->position = pos; };
      glm::vec3 getPosition(){ return this->position; };
      void setRotation(glm::mat4 rot){ this->rotation = rot; };
      glm::mat4 getRotation(){ return this->rotation; };
      unsigned int getShaderType(){ return shaderType; };
      void setShaderType(unsigned int shaderType){ this->shaderType = shaderType; };

    protected:
      virtual void RenderMe();
      std::list<std::unique_ptr<Node> > nodeList;
      glm::vec3 position;
      glm::mat4 rotation;
      unsigned int shaderType;
  };
}


#endif
