#include <spdlog/spdlog.h>

#include "app.h"

int main()
{
#ifdef _DEBUG
	spdlog::set_level(spdlog::level::trace);
#else
	spdlog::set_level(spdlog::level::info);
#endif
	app app;
	app.run();
	return 0;
}