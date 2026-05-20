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
{
	glCreateVertexArrays(1, &vao);
	

	GLuint vbo, ebo;

	glCreateBuffers(1, &vbo);
	glNamedBufferStorage(vbo, sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);

	glCreateTextures(GL_TEXTURE_2D, 1, &texBuf);
}

Renderer::~Renderer()
{

}