#ifndef RENDERER_H
#define RENDERER_H

#include "Shader.h"
#include "Tex.h"
#include "Mesh.h"
#include "Transform.h"
#include <glew.h>
#include <iostream>
#include "Context.h"


class Renderer
{
public:
	void Render(Camera* camera);
	static Renderer& Instance();
	static void Destroy();

private:
	Renderer() {};
	virtual ~Renderer();
	static void Initialization();

	static Shader _shader;
	static Tex _texture;
	static Mesh _mesh;
	static Transform _transform;
};

#endif