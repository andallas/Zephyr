#ifndef RENDERER_H
#define RENDERER_H

#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Transform.h"


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
	static Texture _texture;
	static Mesh _mesh;
	static Transform _transform;
};

#endif