#version 330 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);

	// TODO: remove this hacky solution of inverting the image on the y axis. Load images properly.
	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}