#ifndef NODE_H
#define NODE_H

namespace photon
{
  class Node
  {
    public:
      Node();
      void Render();

    protected:
      virtual void RenderMe() = 0;

  };
}


#endif
