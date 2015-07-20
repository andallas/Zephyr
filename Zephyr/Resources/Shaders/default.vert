#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

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
	Normal = mat3(transpose(inverse(model))) * normal;
	FragPos = vec3(model * vec4(position, 1.0f));
	TexCoords = texCoords;
}