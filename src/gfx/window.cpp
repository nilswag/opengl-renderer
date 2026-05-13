#include <stdexcept>
#include <string>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "window.h"

Window::Window(int width, int height, const std::string& title)
	: width(width), height(height)
{
	if (!glfwInit())
		throw std::runtime_error("Unable to initialize glfw");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!window)
		throw std::runtime_error("Unable to initialize glfw window");

	glfwMakeContextCurrent(window);

	if (!gladLoadGL(static_cast<GLADloadfunc>(glfwGetProcAddress)))
		throw std::runtime_error("Unable to initialize glad");
}

Window::~Window()
{
	if (window)
		glfwDestroyWindow(window);
	glfwTerminate();
}