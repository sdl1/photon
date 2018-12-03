#ifndef BASICSHAPES_H
#define BASICSHAPES_H

#include "Node.h"
#include "Mesh.h"

namespace photon
{
  namespace shapes
  {
    class Cube : public Node
    {
      public:
        Cube(float L, glm::vec3 colour = glm::vec3(1.0f, 1.0f, 1.0f));
        virtual ~Cube();

      private:
        float L;
        photon::Mesh *mesh;
        void RenderMe();
    };

    class Square : public Node
    {
      public:
        Square(float L, glm::vec3 colour = glm::vec3(1.0f, 1.0f, 1.0f));
        virtual ~Square();

      private:
        float L;
        photon::Mesh *mesh;
        void RenderMe();
    };
  }
}

#endif
