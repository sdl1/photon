#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

out vec3 vertex_color;
out vec3 vertex_normal_worldspace;
out vec3 frag_pos_worldspace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  gl_Position = projection * view * model * vec4(position, 1.0f);

  vertex_color = color;

	// Normal matrix to transform normal into worldspace
	// TODO move normal matrix calc out of shader
	vertex_normal_worldspace = mat3(transpose(inverse(model))) * normal;

	frag_pos_worldspace = vec3(model * vec4(position, 1.0f));
}
