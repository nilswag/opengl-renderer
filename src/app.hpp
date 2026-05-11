#pragma once
#include <string>
#include <GLFW/glfw3.h>

class App
{
public:
	App(int width, int height, const std::string& title);
	~App();

	App() = delete;
	App(const App&) = delete;
	App& operator=(const App&) = delete;

	void run();

private:
	GLFWwindow* window;
};