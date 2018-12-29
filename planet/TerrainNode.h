#ifndef TERRAINNODE_H
#define TERRAINNODE_H

#include "Node.h"
#include "Mesh.h"

class TerrainNode : public photon::Node
{
  public:
    TerrainNode(float L, std::function<float(glm::vec3)> height);
    virtual ~TerrainNode();

  private:
    float L;
    void RenderMe();
    std::vector<std::unique_ptr<photon::Mesh> > quadrants;
};

#endif
