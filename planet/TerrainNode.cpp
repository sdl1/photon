#include <GL/glew.h>

#include "TerrainNode.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

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

TerrainNode::TerrainNode(float L, std::function<float(glm::vec3)> height_fn, glm::vec3 origin) :
  L(L), height_fn(height_fn), origin(origin)
{
  // TODO remove origin, it's redundant
  mesh = generateMesh(origin, L, height_fn);
  active = true;
  quadrantCentre = origin + glm::vec3(L/2, L/2, 0);
  quadrantCentre[2] = height_fn(quadrantCentre);
}

TerrainNode::~TerrainNode()
{
  delete mesh;
}

void TerrainNode::RenderMe()
{
  if(active) mesh->drawStrip();
}

void TerrainNode::updateLOD(glm::vec3 pos, glm::vec3 front, glm::mat4 model)
{
  // The model matrix is accumulated to children, so that we calcualte the distance in world space
  // Get the quadrant centre in worldspace
  // TODO tidy this up in photon, we should be able to directly access the model matrix for this node
  model = glm::translate(model, this->position);
  model = model * this->rotation;
  glm::vec3 worldQuadrantCentre = glm::vec3(model*glm::vec4(quadrantCentre, 1.0));

  // Recurse to children first
  for(auto & child : nodeList)
  {
    dynamic_cast<TerrainNode*>(child.get())->updateLOD(pos, front, model);
  }

  float minL = 0.1f;
  float LIM = 0.5f;
  // d is distance from camera to centre of a quadrant
  // L is width of a quadrant
  // W = L/d ~= apparent width of the quadrant
  // We want W to stay ~constant
  float d = length(pos - worldQuadrantCentre);

  //float d = length(pos - quadrantCentre);
  float W = L/std::max(d, 1e-6f);

  // Active quadrants are candidates for splitting
  // Stop splitting at some point
  if(active && L>minL)
  {
    // Split the quadrant if it appears too big
    if(W>LIM)
    {
      split();
      // If we've split, we don't want to merge by definition
      return;
    }
  }


  // MERGING
  // Non-active quadrants are candidates for merging
  if(!active)
  {
    // A non-active quadrant corresponds to a child TerrainNode.
    // We only merge this quadrant if all the quadrants of the
    // child TerrainNode are active, i.e. the child TerrainNode
    // is not split.
    bool allChildrenActive = true;
    for(auto & child : nodeList)
    {
      allChildrenActive = allChildrenActive && dynamic_cast<TerrainNode*>(child.get())->active;
    }
    if(allChildrenActive)
    {
      // Merge the quadrant if it doesn't appear too big
      // It's important that this is consistent with the
      // splitting criterion, to avoid loops
      if(W<=LIM)
      {
        merge();
      }
    }
  }
}

void TerrainNode::split()
{
  assert(active);
  // TODO just re-activate children rather than deleting
  float dx = L/2.0;
  const glm::vec3 offset[] = {
    glm::vec3(0,0,0),
    glm::vec3(dx,0,0),
    glm::vec3(dx,dx,0),
    glm::vec3(0,dx,0),
  };
  for(int i=0 ; i<4 ; i++)
  {
    glm::vec3 neworigin = origin + offset[i];
    addChild(new TerrainNode(dx, height_fn, neworigin));
  }
  active = false;
}

void TerrainNode::merge()
{
  assert(!active);
  // TODO just de-activate children rather than deleting
  nodeList.clear();
  active = true;
}


