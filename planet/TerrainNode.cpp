#include <GL/glew.h>

#include "TerrainNode.h"

#include <iostream>

using photon::Mesh;

// Origin is bottom-left corner
Mesh *generateMesh(glm::vec3 origin, float sideLength)
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
      vertices[9*idx + 0] = origin[0] + c*dx;
      vertices[9*idx + 1] = origin[1] + r*dx;//0;
      vertices[9*idx + 2] = origin[2] + 0;//-r*dx;

      vertices[9*idx + 3] = 0;
      vertices[9*idx + 4] = 1;
      vertices[9*idx + 5] = 0;

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

TerrainNode::TerrainNode(float L) :
  L(L)
{
  float dx = L/2.0;
  // Four quadrants
  quadrants.push_back(std::unique_ptr<Mesh>(generateMesh(glm::vec3(0,0,0), dx)) );
  quadrants.push_back(std::unique_ptr<Mesh>(generateMesh(glm::vec3(dx,0,0), dx)) );
  quadrants.push_back(std::unique_ptr<Mesh>(generateMesh(glm::vec3(dx,dx,0), dx)) );
  quadrants.push_back(std::unique_ptr<Mesh>(generateMesh(glm::vec3(0,dx,0), dx)) );
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


