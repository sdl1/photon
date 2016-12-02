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
        Cube(float L);
        virtual ~Cube();

      private:
        float L;
        photon::Mesh *mesh;
        void RenderMe();
    };
  }
}

#endif
