#ifndef PLANET_H
#define PLANET_H

#include "Node.h"
#include "TerrainNode.h"

class Planet : public photon::Node
{
  public:
    Planet(float L, std::function<float(glm::vec3)> height_fn);
    virtual ~Planet();
    void updateLOD(glm::vec3 pos, glm::vec3 front);

  private:
    float L;
    std::function<float(glm::vec3)> height_fn;
    void RenderMe();
};

#endif
