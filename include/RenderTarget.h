#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#include <string>

namespace photon
{

  class RenderTarget
  {
    public:
      unsigned int fbo;

  };

  class RenderTargetImage : public RenderTarget
  {
    public:
      RenderTargetImage(std::string const &filename);
    private:
      std::string filename;
  };

}

#endif
