#ifndef MESH_H
#define MESH_H

#include <vector>

#include <glm/glm.hpp>

namespace photon
{
  class Mesh
  {
    public:
      struct Vertex
      {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec3 Color;
      };

      Mesh(std::vector<Vertex>, std::vector<GLuint>); // texture
      // Specify vertices in interleaved form
      Mesh(GLfloat vertices[], int numVertices, std::vector<GLuint>); // texture
      void draw();
      void drawWithIndices();
      void drawStrip();

    private:
      int numVertices;
      std::vector<Vertex> vertices;
      std::vector<GLuint> indices;
      // Vertex array object
      GLuint VAO;
      // Vertex buffer object
      GLuint VBO;
      // Element buffer object
      GLuint EBO;
      void setup();
  };
}

#endif
