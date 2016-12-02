#include "Shader.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// TODO automatically reload from file

namespace photon
{

  Shader::Shader(std::string vertexShaderFilename, std::string fragmentShaderFilename) :
    vertexShaderFilename(vertexShaderFilename), fragmentShaderFilename(fragmentShaderFilename)
  {
    std::string vshader_src = readFromFile(vertexShaderFilename);
    const char* vsrc = vshader_src.c_str();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vsrc, nullptr);
    glCompileShader(vertexShader);
    checkShaderForErrors(vertexShader);

    std::string fshader_src = readFromFile(fragmentShaderFilename);
    const char* fsrc = fshader_src.c_str();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fsrc, nullptr);
    glCompileShader(fragmentShader);
    checkShaderForErrors(fragmentShader);

    this->program = glCreateProgram();
    glAttachShader(this->program, vertexShader);
    glAttachShader(this->program, fragmentShader);
    glLinkProgram(this->program);
    checkProgramForErrors(this->program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
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
    }

  template<>
    void Shader::setUniform(std::string uniformName, glm::mat4 val)
    {
      this->use();
      // TODO error handling - exceptions
      GLuint uniformLoc = glGetUniformLocation(this->program, uniformName.c_str());
      glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(val));
    }

  std::string Shader::readFromFile(std::string filename) const
  {
    // TODO improve this
    std::stringstream output;
    std::ifstream file;
    std::string line;
    file.open(filename);
    while(getline(file, line))
    {
      output << line << std::endl;
    }
    file.close();
    return output.str();
  }

  void Shader::checkShaderForErrors(GLuint shader) const
  {
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(shader, 512, nullptr, infoLog);
      std::cout << "Error in shader compilation:\n" << infoLog << "\n";
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

