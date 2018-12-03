#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"

namespace photon
{
  Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices) :
    vertices(vertices), indices(indices)
  {
    this->setup();
  }

  Mesh::Mesh(GLfloat v[], int numVertices, std::vector<GLuint> indices) :
    indices(indices)
  {
    // TODO can just buffer directly...
    std::vector<Vertex> vertices(numVertices);
    for(int i=0 ; i<numVertices ;i++)
    {
      vertices[i].Position = glm::vec3(v[i*9 + 0], v[i*9 + 1], v[i*9 + 2]);
      vertices[i].Normal = glm::vec3(v[i*9 + 3], v[i*9 + 4], v[i*9 + 5]);
      vertices[i].Color = glm::vec3(v[i*9 + 6], v[i*9 + 7], v[i*9 + 8]);
    }
    this->vertices = vertices;
    this->setup();
  }

  void Mesh::setup()
  {
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    //1. Bind Vertex Array Object
    glBindVertexArray(this->VAO);
    //2. Copy our vertices array in a buffer for OpenGL to use
    // Bind to GL_ARRAY_BUFFER target
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    // Copy data across
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size()*sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
    //3 Copy across index array data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size()*sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
    //3. Set our vertex attribute pointers
    // Pass information to location 0 (see vertex shader)
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);
    // Colour attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Color));
    glEnableVertexAttribArray(2);

    // vertex attribute 0 is now associated with the data in VBO
    // 4. Unbind the VAO
    glBindVertexArray(0);
  }

  void Mesh::draw()
  {
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // With indices (element buffer object)
    //glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

}
