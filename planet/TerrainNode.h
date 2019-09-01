#ifndef TERRAINNODE_H
#define TERRAINNODE_H

#include "Node.h"
#include "Mesh.h"

class TerrainNode : public photon::Node
{
  public:
    TerrainNode(float L, std::function<float(glm::vec3)> height_fn, glm::vec3 origin = glm::vec3(0,0,0));
    virtual ~TerrainNode();
    void updateLOD(glm::vec3 pos, glm::vec3 front, glm::mat4 model = glm::mat4());
    void split();
    void merge();

  private:
    float L;
    std::function<float(glm::vec3)> height_fn;
    glm::vec3 origin;
    void RenderMe();
    photon::Mesh *mesh;
    bool active;
    glm::vec3 quadrantCentre;
};

#endif
