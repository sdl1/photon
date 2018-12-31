#ifndef TERRAINNODE_H
#define TERRAINNODE_H

#include "Node.h"
#include "Mesh.h"

class TerrainNode : public photon::Node
{
  public:
    TerrainNode(float L, std::function<float(glm::vec3)> height_fn, glm::vec3 origin = glm::vec3(0,0,0));
    virtual ~TerrainNode();
    void updateLOD(glm::vec3 pos, glm::vec3 front);
    void split(int quadrant);

  private:
    float L;
    std::function<float(glm::vec3)> height_fn;
    glm::vec3 origin;
    void RenderMe();
    std::vector<std::unique_ptr<photon::Mesh> > quadrants;
    bool active[4];
    glm::vec3 quadrantCentres[4];
};

#endif
