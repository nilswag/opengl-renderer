#include <stdexcept>
#include <print>
#include <glad/gl.h>
#include "gfx/window.hpp"
#include "gfx/renderer.hpp"
#include "gfx/shader.hpp"

int main()
{
	try
	{
		const int width = 800;
		const int height = 800;
		Window window(width, height, "OpenGL");

		ShaderProgram test = ShaderProgram::createGraphics("shaders/vertex.glsl", "shaders/fragment.glsl");

		//Renderer renderer(width, height);

		while (!window.shouldClose())
		{
			window.pollEvents();

			float color[3] = { 0.0f };
			glClearNamedFramebufferfv(0, GL_COLOR, 0, color);
			window.swapBuffers();
		}
	}
	catch (const std::exception& e)
	{
		std::println("{}", e.what());
	}

	return 0;
}