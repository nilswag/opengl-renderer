#include <glad/gl.h>
#include "renderer.hpp"

static float vertices[] = {
	-1.0f, -1.0f,	// bottom left
	 1.0f, -1.0f,	// bottom right
	 1.0f,  1.0f,	// top right
	-1.0f,  1.0f	// top left
};

static unsigned int indices[] = {
	0, 1, 2,	// bottom right triangle
	0, 2, 3		// top left triangle
};

Renderer::Renderer()
	: vao(0), vbo(0), texBuf(0)
{
	GLuint vbo, ebo;

	// configure vbo for quad
	glCreateBuffers(1, &vbo);
	glNamedBufferStorage(vbo, sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);

	// configure indices for quad
	glCreateBuffers(1, &ebo);
	glNamedBufferStorage(ebo, sizeof(indices), indices, GL_DYNAMIC_STORAGE_BIT);

	// configure vao
	glCreateVertexArrays(1, &vao);
	glVertexArrayVertexBuffer(vao, 0, vbo, 0, 2 * sizeof(float));
	glVertexArrayElementBuffer(vao, ebo);

	glEnableVertexArrayAttrib(vao, 0);

	glVertexAttribFormat(0, 2, GL_FLOAT, GL_FALSE, 0);

	glVertexArrayAttribBinding(vao, 0, 0);
}

Renderer::~Renderer()
{

}