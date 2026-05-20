#pragma once
#include <glad/gl.h>
#include "shader.hpp"

class Renderer
{
public:
	Renderer(int width, int height);
	~Renderer();

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer&&) = delete;

	void flush();

private:
	GLuint vao, vbo, texBuf;
	ShaderProgram graphicsShader, computeShader;
};
