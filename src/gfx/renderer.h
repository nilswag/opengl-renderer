#pragma once
#include <glm/glm.hpp>

struct QuadInstance
{
	QuadInstance(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& color);

	glm::mat4 m_model;
	glm::vec4 m_color;
};

class Renderer
{

};