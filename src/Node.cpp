#include "Node.h"
#include <glm/gtc/matrix_transform.hpp>

namespace photon
{

  Node::Node() :
    position(glm::vec3(0.0f, 0.0f, 0.0f)),
    shaderType(0)
  {
  }

  Node::~Node()
  {
    nodeList.clear();
  }

  void Node::addChild(Node *node)
  {
    this->nodeList.push_back(std::unique_ptr<Node>(node));
  }

  void Node::RenderMe()
  {
    return;
  }
}
