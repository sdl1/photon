#version 330 core

in vec3 vertexColor; // Same name and type as vertex shader => linked

out vec4 color;

//uniform vec4 ourColor;

void main()
{
  color = vec4(vertexColor, 1.0f);
}
