#version 330 core

in vec3 vertex_color; // Same name and type as vertex shader => linked
in vec3 vertex_normal_worldspace;
in vec3 frag_pos_worldspace;

out vec4 color;

uniform vec3 light_pos;
uniform vec3 light_color;

void main()
{
  //color = vec4(vertex_color, 1.0f);

  float ambient_strength = 0.3;
  vec3 ambient = ambient_strength * light_color;

	vec3 normal = normalize(vertex_normal_worldspace);
	vec3 lightdir = normalize(light_pos - frag_pos_worldspace);
	float diffuse_strength = max(dot(normal, lightdir), 0.0f);
	vec3 diffuse = diffuse_strength * light_color;

  color = vec4((ambient + diffuse) * vertex_color, 1.0f);
}
