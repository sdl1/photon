#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <GL/glew.h>

namespace photon
{
  class Shader
  {
    public:
      Shader();
      Shader(std::string vertexShaderFilename, std::string fragmentShaderFilename);
      void use() const;
      template<typename T> void setUniform(std::string uniformName, T val);

    private:
      GLuint program;
      std::string readFromFile(std::string filename) const;
      void checkShaderForErrors(GLuint shader, std::string shaderFilename) const;
      void checkProgramForErrors(GLuint program) const;
      std::string vertexShaderFilename;
      std::string fragmentShaderFilename;

  };
}

#endif
