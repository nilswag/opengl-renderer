#include <stdexcept>
#include <print>
#include <glad/gl.h>
#include "gfx/window.hpp"
#include "gfx/shader.hpp"

int main()
{
	try
	{
		Window window(800, 800, "OpenGL");

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