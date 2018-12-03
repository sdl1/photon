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
    public:
      Node();
      virtual ~Node();
      void addChild(Node *node);
      virtual void Render();
      virtual void Render(photon::Shader &shader);
      virtual void Render(photon::Shader &shader, glm::mat4 model);
      void setPosition(glm::vec3 pos){ this->position = pos; };
      glm::vec3 getPosition(){ return this->position; };

    protected:
      virtual void RenderMe();
      std::list<std::unique_ptr<Node> > nodeList;
      glm::vec3 position;
  };
}


#endif
