#include "Renderer.h"


void Renderer::Render(Camera* camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_shader.Bind();
	_texture.Bind(0);
	_shader.Update(_transform, camera);
	_mesh.Draw();
}

Renderer& Renderer::Instance()
{
	static Renderer* instance = NULL;
	if (instance == NULL)
	{
		Renderer::Initialization();

		instance = new Renderer();
	}

	return *instance;
}

void Renderer::Destroy()
{
	Renderer* renderer = &Instance();
	delete renderer;
}

// Private
Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Initialization()
{
	ShaderInfo shaders[] = 
	{
		{ GL_VERTEX_SHADER, "default.vert" },
		{ GL_FRAGMENT_SHADER, "default.frag" },
		{ GL_NONE, "" }
	};

	_shader.init(shaders);
	_texture.init("texture.png");
	_mesh.init("mesh.obj");
	_transform.GetPos().z = -100;
}