#pragma once
#include <string>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();

private:
	GLFWwindow* window;
	int width, height;
};