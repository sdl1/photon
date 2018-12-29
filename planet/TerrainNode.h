#ifndef TERRAINNODE_H
#define TERRAINNODE_H

#include "Node.h"
#include "Mesh.h"

class TerrainNode : public photon::Node
{
  public:
    TerrainNode(float L);
    virtual ~TerrainNode();

  private:
    float L;
    //photon::Mesh *mesh;
    void RenderMe();
    //std::vector<photon::Mesh*> quadrants;
    std::vector<std::unique_ptr<photon::Mesh> > quadrants;
};

#endif
