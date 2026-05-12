#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <print>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include "app.hpp"

static VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(
	vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
	vk::DebugUtilsMessageTypeFlagBitsEXT type,
	const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* puserData
)
{
	// TODO: actually divide logging severity into sections

	std::string typeStr = [type]() {
			switch (type)
			{
			case vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral: return "GENERAL";
			case vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation: return "VALIDATION";
			case vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance: return "PERFORMANCE";
			default: return "N/A";
			}
		}();

	std::println(std::cerr, "validation layer: {} msg: {}", typeStr, pCallbackData->pMessage);

	return vk::False;
}

#ifdef _DEBUG
const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};
#else
const std::vector<const char*> validationLayers = { };
#endif

void App::createInstance()
{
	// vulkan application info
	vk::ApplicationInfo appInfo = { };
	appInfo.pApplicationName = title.c_str();
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = vk::ApiVersion14;

	// check if required glfw extensions for vulkan are available
	auto requiredExtensions = getRequiredInstanceExtentions();
	auto extensionProperties = context.enumerateInstanceExtensionProperties();
	auto unsupportedPropertyIt = std::ranges::find_if(requiredExtensions,
		[&extensionProperties](const auto& requiredExtension) {
			return std::ranges::none_of(extensionProperties, [requiredExtension](const auto& extensionProperty)
				{
					return strcmp(extensionProperty.extensionName, requiredExtension) == 0;
				});
		});
	if (unsupportedPropertyIt != requiredExtensions.end())
	{
		throw std::runtime_error("Required extension not supported: " + std::string(*unsupportedPropertyIt));
	}

	// vulkan instance info
	vk::InstanceCreateInfo createInfo = {};
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledLayerCount = validationLayers.size();
	createInfo.ppEnabledLayerNames = validationLayers.data();
	createInfo.enabledExtensionCount = requiredExtensions.size();
	createInfo.ppEnabledExtensionNames = requiredExtensions.data();

	instance = vk::raii::Instance(context, createInfo);
	
	// check if all specified validation layers are available
	auto layerProperties = context.enumerateInstanceLayerProperties();
	auto unsupportedLayerIt = std::ranges::find_if(validationLayers,
		[&layerProperties](const auto& requiredLayer) {
			return std::ranges::none_of(layerProperties, [requiredLayer](const auto& layerProperty)
				{ return strcmp(layerProperty.layerName, requiredLayer) == 0; });
		});
	if (unsupportedLayerIt != validationLayers.end())
	{
		throw std::runtime_error("Required validation layer not supported: " + std::string(*unsupportedLayerIt));
	}
}

std::vector<const char*> App::getRequiredInstanceExtentions()
{
	unsigned int glfwExtensionCount = 0;
	auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifdef _DEBUG
	extensions.push_back(vk::EXTDebugUtilsExtensionName);
#endif

	return extensions;
}

App::App(int width, int height, const std::string& title)
	: width(width), height(height), title(title), instance(nullptr)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	createInstance();


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