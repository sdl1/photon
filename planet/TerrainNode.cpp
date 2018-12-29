#include <GL/glew.h>

#include "TerrainNode.h"

#include <iostream>

using photon::Mesh;

// Origin is bottom-left corner
Mesh *generateMesh(glm::vec3 origin, float sideLength, std::function<float(glm::vec3)> f)
{
  glm::vec3 colour(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX);

  int rows = 9;
  int columns = 9;
  int numVertices = rows*columns;
  // 81 vertices
  // Position, normal, color
  GLfloat vertices[numVertices*9];
  float dx = sideLength/8.0;
  for(int r=0 ; r<rows ; r++)
  {
    for(int c=0 ; c<columns ; c++)
    {
      int idx = r*columns + c;
      float x = origin[0] + c*dx;
      float y = origin[1] + r*dx;
      float h = f(glm::vec3(x,y,0));
      float z = origin[2] + h;
      vertices[9*idx + 0] = x;
      vertices[9*idx + 1] = y;
      vertices[9*idx + 2] = z;

      // normal = -(dhdx, dhdy, -1)
      float eps = 1e-6;
      float dhdx = (f(glm::vec3(x+eps,y,0)) - h)/eps;
      float dhdy = (f(glm::vec3(x,y+eps,0)) - h)/eps;
      glm::vec3 normal(dhdx, dhdy, -1);
      normal = -normalize(normal);

      vertices[9*idx + 3] = normal[0];
      vertices[9*idx + 4] = normal[1];
      vertices[9*idx + 5] = normal[2];

      vertices[9*idx + 6] = colour[0];
      vertices[9*idx + 7] = colour[1];
      vertices[9*idx + 8] = colour[2];
    }
  }

  // Indices
  std::vector<GLuint> indices;
  for(int r = 0; r < rows - 1; r++)
  {
    indices.push_back( r * columns );
    for(int c = 0; c < columns; c++)
    {
      indices.push_back( r * columns + c );
      indices.push_back( (r + 1) * columns + c );
    }
    indices.push_back( (r + 1) * columns + (columns - 1) );
  }

  return new Mesh(vertices, numVertices, indices);
}

//TerrainNode::TerrainNode(float L) :
TerrainNode::TerrainNode(float L, std::function<float(glm::vec3)> height_fn) :
  L(L)
{
  float dx = L/2.0;
  // Four quadrants
  quadrants.push_back(std::unique_ptr<Mesh>(generateMesh(glm::vec3(0,0,0), dx, height_fn)) );
  quadrants.push_back(std::unique_ptr<Mesh>(generateMesh(glm::vec3(dx,0,0), dx, height_fn)) );
  quadrants.push_back(std::unique_ptr<Mesh>(generateMesh(glm::vec3(dx,dx,0), dx, height_fn)) );
  quadrants.push_back(std::unique_ptr<Mesh>(generateMesh(glm::vec3(0,dx,0), dx, height_fn)) );
}

TerrainNode::~TerrainNode()
{
  quadrants.clear();
}

void TerrainNode::RenderMe()
{
  for(auto const & q : quadrants)
  {
    q->drawStrip();
  }
}


