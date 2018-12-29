#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <GL/glew.h>

#include <map>
#include <glm/glm.hpp>

namespace photon
{
  class Shader
  {
    public:
      Shader();
      Shader(std::string vertexShaderFilename, std::string fragmentShaderFilename);
      void use() const;
      template<typename T> void setUniform(std::string uniformName, T val);
      void reload();

    private:
      GLuint program;
      std::string readFromFile(std::string filename) const;
      void checkShaderForErrors(GLuint shader, std::string shaderFilename) const;
      void checkProgramForErrors(GLuint program) const;
      std::string vertexShaderFilename;
      std::string fragmentShaderFilename;
      // Map of uniforms (name-value pairs) so we can reset them later
      // NOTE: need to keep this up to date
      std::map<std::string, float> uniformMap_float;
      std::map<std::string, glm::vec3> uniformMap_vec3;
      std::map<std::string, glm::mat4> uniformMap_mat4;
  };
}

#endif
