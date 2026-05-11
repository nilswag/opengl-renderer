#include <stdexcept>
#include <iostream>
#include <print>
#include "app.hpp"

int main()
{
	try
	{
		App app;
		app.run();
	}
	catch (const std::exception& e)
	{
		std::println(std::cerr, "Error: {}", e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
