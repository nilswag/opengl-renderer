#pragma once
#include <string>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(Window&&) = delete;

	bool shouldClose() const;
	void pollEvents() const;
	void swapBuffers() const;

private:
	void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	GLFWwindow* window;
	int width, height;
};