#include <glad/gl.h>
#include "shader.hpp"
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

Renderer::Renderer(int width, int height)
	: vao(0), vbo(0), texBuf(0),
	graphicsShader(ShaderProgram::createGraphics("shaders/vertex.glsl", "shaders/fragment.glsl")),
	computeShader(ShaderProgram::createCompute("shaders/raytracing.glsl"))
{
	// configure vbo for quad
	glCreateBuffers(1, &vbo);
	glNamedBufferStorage(vbo, sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);

	// configure indices for quad
	GLuint ebo;
	glCreateBuffers(1, &ebo);
	glNamedBufferStorage(ebo, sizeof(indices), indices, GL_DYNAMIC_STORAGE_BIT);

	// configure vao
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glVertexArrayVertexBuffer(vao, 0, vbo, 0, 2 * sizeof(float));
	glVertexArrayElementBuffer(vao, ebo);

	glEnableVertexArrayAttrib(vao, 0);

	glVertexAttribFormat(0, 2, GL_FLOAT, GL_FALSE, 0);

	glVertexArrayAttribBinding(vao, 0, 0);
	
	// congifure buffer texture
	glCreateTextures(GL_TEXTURE_2D, 1, &texBuf);
	glTextureStorage2D(texBuf, 1, GL_RGBA32F, width, height);
}

Renderer::~Renderer()
{
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glDeleteTextures(1, &texBuf);
}

void Renderer::flush()
{

}