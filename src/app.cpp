#include <string>
#include <GLFW/glfw3.h>
#include "app.hpp"

App::App(int width, int height, const std::string& title)
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
}

App::~App()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void App::run()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
}