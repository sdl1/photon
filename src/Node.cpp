#include "Node.h"
#include <glm/gtc/matrix_transform.hpp>

namespace photon
{

  Node::Node() :
    position(glm::vec3(0.0f, 0.0f, 0.0f))
  {
  }

  Node::~Node()
  {
  }

  void Node::addChild(Node *node)
  {
//this->nodeList.push_back(std::make_unique<Node>(node));
    this->nodeList.push_back(std::unique_ptr<Node>(node));
  }

  void Node::Render()
  {
    photon::Shader shader("shaders/default.vert", "shaders/default.frag");
    Render(shader, glm::mat4());
  }

  void Node::Render(photon::Shader &shader)
  {
    Render(shader, glm::mat4());
  }

  void Node::Render(photon::Shader &shader, glm::mat4 model)
  {
    shader.use();
    model = glm::translate(model, this->position);
    shader.setUniform("model", model);
    this->RenderMe();
    for(auto const & child : this->nodeList)
    {
      child->Render(shader, model);
    }
    model = glm::translate(model, -this->position);
  }

  void Node::RenderMe()
  {
    return;
  }
}
