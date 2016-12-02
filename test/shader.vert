#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float offset;

void main()
{
  //gl_Position = vec4(position.x + offset, position.yz, 1.0);
  //gl_Position = vec4(position.xyz, 1.0);
  gl_Position = projection * view * model * vec4(position, 1.0f);
  //vertexColor = color + gl_Position.xyz;//vec4(0.5, 0, 0, 1);
  vertexColor = color;
}
