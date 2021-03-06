#include <GL/glew.h>

#include "BasicShapes.h"

namespace photon
{
  namespace shapes
  {

    Cube::Cube(float L, glm::vec3 colour) :
      L(L)
    {
      // Position, normal, color
/*
      GLfloat vertices[] = {-0.5, -0.5, -0.5,  1,0,0,  1,0,0,
                            0.5, -0.5, -0.5,   1,0,0,  1,0,0,
                            0.5, 0.5, -0.5,    1,0,0,  0,0,1,
                            -0.5, 0.5, -0.5,   1,0,0,  1,0,1,
                            -0.5, -0.5, 0.5,   1,0,0,  1,1,0,
                            0.5, -0.5, 0.5,    1,0,0,  0,1,0,
                            0.5, 0.5, 0.5,     1,0,0,  0,1,1,
                            -0.5, 0.5, 0.5,    1,0,0,  1,1,1};
*/
      GLfloat vertices[] = {-0.5, -0.5, -0.5,  0,0,-1,  1,0,0,
                            0.5, 0.5, -0.5,    0,0,-1,  0,0,1,
                            0.5, -0.5, -0.5,   0,0,-1,  1,0,0,
                            0.5, 0.5, -0.5,    0,0,-1,  0,0,1,
      											-0.5, -0.5, -0.5,  0,0,-1,  1,0,0,
                            -0.5, 0.5, -0.5,   0,0,-1,  1,0,1,

      											-0.5, -0.5, -0.5,  0,-1,0,  1,0,0,
                            0.5, -0.5, -0.5,   0,-1,0,  1,0,0,
                            0.5, -0.5, 0.5,    0,-1,0,  0,1,0,
                            0.5, -0.5, 0.5,    0,-1,0,  0,1,0,
                            -0.5, -0.5, 0.5,   0,-1,0,  1,1,0,
      											-0.5, -0.5, -0.5,  0,-1,0,  1,0,0,

                            0.5, -0.5, -0.5,   1,0,0,  1,0,0,
                            0.5, 0.5, -0.5,    1,0,0,  0,0,1,
                            0.5, -0.5, 0.5,    1,0,0,  0,1,0,
                            0.5, 0.5, -0.5,    1,0,0,  0,0,1,
                            0.5, 0.5, 0.5,     1,0,0,  0,1,1,
                            0.5, -0.5, 0.5,    1,0,0,  0,1,0,

                            0.5, 0.5, -0.5,    0,1,0,  0,0,1,
                            -0.5, 0.5, -0.5,   0,1,0,  1,0,1,
                            -0.5, 0.5, 0.5,    0,1,0,  1,1,1,
                            0.5, 0.5, -0.5,    0,1,0,  0,0,1,
                            -0.5, 0.5, 0.5,    0,1,0,  1,1,1,
                            0.5, 0.5, 0.5,     0,1,0,  0,1,1,

      											-0.5, -0.5, -0.5,  -1,0,0,  1,0,0,
                            -0.5, -0.5, 0.5,   -1,0,0,  1,1,0,
                            -0.5, 0.5, 0.5,    -1,0,0,  1,1,1,
      											-0.5, -0.5, -0.5,  -1,0,0,  1,0,0,
                            -0.5, 0.5, 0.5,    -1,0,0,  1,1,1,
                            -0.5, 0.5, -0.5,   -1,0,0,  1,0,1,

                            -0.5, -0.5, 0.5,   0,0,1,  1,1,0,
                            0.5, -0.5, 0.5,    0,0,1,  0,1,0,
                            0.5, 0.5, 0.5,     0,0,1,  0,1,1,
                            0.5, 0.5, 0.5,     0,0,1,  0,1,1,
                            -0.5, 0.5, 0.5,    0,0,1,  1,1,1,
                            -0.5, -0.5, 0.5,   0,0,1,  1,1,0};



      for(int v=0 ; v<36 ; v++)
      {
        for(int i=0 ; i<3 ; i++)
        {
          vertices[9*v + i] *= L;
        }
        for(int i=6 ; i<9 ; i++)
        {
          vertices[9*v + i] = colour[i-6];
        }
      }

      /*
      std::vector<GLuint> indices {0, 2, 1,
                                   2, 0, 3,
                                   0, 1, 5,
                                   5, 4, 0,
                                   1, 2, 5,
                                   2, 6, 5,
                                   2, 3, 7,
                                   2, 7, 6,
                                   0, 4, 7,
                                   0, 7, 3,
                                   4, 5, 6,
                                   6, 7, 4};
                                   */

      std::vector<GLuint> indices(36);
      for(int i=0 ; i<36 ; i++) indices[i] = i;
                                   

      //this->mesh = new photon::Mesh(vertices, 8, indices);
      this->mesh = new photon::Mesh(vertices, 36, indices);
    }

    Cube::~Cube()
    {
      delete this->mesh;
    }

    void Cube::RenderMe()
    {
      this->mesh->draw();
    }

    Square::Square(float L, glm::vec3 colour) :
      L(L)
    {
      // Position, normal, color
      
      GLfloat vertices[] = {0.5, 0.0, -0.5,    0,1,0,  0,0,1,
                            -0.5, 0.0, -0.5,   0,1,0,  1,0,1,
                            -0.5, 0.0, 0.5,    0,1,0,  1,1,1,
                            0.5, 0.0, -0.5,    0,1,0,  0,0,1,
                            -0.5, 0.0, 0.5,    0,1,0,  1,1,1,
                            0.5, 0.0, 0.5,     0,1,0,  0,1,1};


      for(int v=0 ; v<6 ; v++)
      {
        for(int i=0 ; i<3 ; i+=2)
        {
          vertices[9*v + i] *= L;
        }
        for(int i=6 ; i<9 ; i++)
        {
          vertices[9*v + i] = colour[i-6];
        }
      }

      std::vector<GLuint> indices {0, 1, 2,
                                   3, 4, 5};

      this->mesh = new photon::Mesh(vertices, 6, indices);
    }

    Square::~Square()
    {
      delete this->mesh;
    }

    void Square::RenderMe()
    {
      this->mesh->draw();
    }

  }

}
