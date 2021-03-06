#include "Shader.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

namespace photon
{

  Shader::Shader()
  {
  }

  Shader::Shader(std::string vertexShaderFilename, std::string fragmentShaderFilename) :
    vertexShaderFilename(vertexShaderFilename), fragmentShaderFilename(fragmentShaderFilename)
  {
    reload();
  }

  void Shader::use() const
  {
    glUseProgram(this->program);
  }

  template<>
    void Shader::setUniform(std::string uniformName, GLfloat val)
    {
      // TODO keep track of current prgram and restore it after...
      this->use();
      // TODO error handling - exceptions
      GLuint uniformLoc = glGetUniformLocation(this->program, uniformName.c_str());
      glUniform1f(uniformLoc, val);
      uniformMap_float[uniformName] = val;
    }

  template<>
    void Shader::setUniform(std::string uniformName, glm::mat4 val)
    {
      this->use();
      // TODO error handling - exceptions
      GLuint uniformLoc = glGetUniformLocation(this->program, uniformName.c_str());
      glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(val));
      uniformMap_mat4[uniformName] = val;
    }

  template<>
    void Shader::setUniform(std::string uniformName, glm::vec3 val)
    {
      this->use();
      // TODO error handling - exceptions
      GLuint uniformLoc = glGetUniformLocation(this->program, uniformName.c_str());
      glUniform3fv(uniformLoc, 1, glm::value_ptr(val));
      uniformMap_vec3[uniformName] = val;
    }

  void Shader::reload()
  {
    std::string vshader_src = readFromFile(vertexShaderFilename);
    const char* vsrc = vshader_src.c_str();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vsrc, nullptr);
    glCompileShader(vertexShader);
    checkShaderForErrors(vertexShader, vertexShaderFilename);

    std::string fshader_src = readFromFile(fragmentShaderFilename);
    const char* fsrc = fshader_src.c_str();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fsrc, nullptr);
    glCompileShader(fragmentShader);
    checkShaderForErrors(fragmentShader, fragmentShaderFilename);

    this->program = glCreateProgram();
    glAttachShader(this->program, vertexShader);
    glAttachShader(this->program, fragmentShader);
    glLinkProgram(this->program);
    checkProgramForErrors(this->program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Reload uniforms
    // NOTE: need to keep this up to date
    for(auto & it : uniformMap_float)
    {
      setUniform(it.first, it.second);
    }
    for(auto & it : uniformMap_vec3)
    {
      setUniform(it.first, it.second);
    }
    for(auto & it : uniformMap_mat4)
    {
      setUniform(it.first, it.second);
    }
  }

  std::string Shader::readFromFile(std::string filename) const
  {
    // TODO improve this
    std::stringstream output;
    std::string line;
    std::ifstream file(filename);
    if(!file)
    {
      std::cerr << "Couldn't open file: " << filename << "\n";
    }
    while(getline(file, line))
    {
      output << line << std::endl;
    }
    file.close();
    return output.str();
  }

  void Shader::checkShaderForErrors(GLuint shader, std::string shaderFilename) const
  {
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(shader, 512, nullptr, infoLog);
      std::cout << "Error compiling " << shaderFilename << ":\n" << infoLog << "\n";
    }
  }

  void Shader::checkProgramForErrors(GLuint program) const
  {
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
      glGetProgramInfoLog(program, 512, nullptr, infoLog);
      std::cout << "Error in program linking:\n" << infoLog << "\n";
    }
  }

}

