#include <GL/glew.h>

#include "BasicShapes.h"

namespace photon
{
  namespace shapes
  {

    Cube::Cube(float L) :
      L(L)
    {
      GLfloat vertices[] = {-0.5, -0.5, 0.0,  1,0,0,
                            0.5, -0.5, 0.0,   0,1,0,
                            0.5, 0.5, 0.0,    0,0,1,
                            -0.5, 0.5, 0.0,   1,1,1};

      std::vector<GLuint> indices {0, 1, 2,
                                   2, 3, 0};

      this->mesh = new photon::Mesh(vertices, 4, indices);
    }

    Cube::~Cube()
    {
      delete this->mesh;
    }

    void Cube::RenderMe()
    {
      this->mesh->draw();
    }

  }

}
