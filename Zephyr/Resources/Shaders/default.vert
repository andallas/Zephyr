#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out VS_OUT
{
	vec3 Normal;
	vec3 FragPos;
	vec2 TexCoords;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	// TODO: See below
	/*
		Inversing matrices is a costly operation even for shaders so wherever possible,
		try to avoid doing inverse operations in shaders since they have to be done on
		each vertex of your scene. For learning purposes this is fine, but for an
		efficient application you'll likely want to calculate the normal matrix on the
		CPU and send it to the shaders via a uniform before drawing (just like the
		model matrix).
	*/
	vs_out.Normal = mat3(transpose(inverse(model))) * normal;
	vs_out.FragPos = vec3(model * vec4(position, 1.0f));
	vs_out.TexCoords = texCoords;
}