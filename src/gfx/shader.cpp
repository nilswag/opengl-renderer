#include <string>
#include <stdexcept>
#include <glad/gl.h>
#include "shader.hpp"
#include "../util/io.h"

ShaderProgram ShaderProgram::createGraphics(const std::string& vertexPath, const std::string& fragmentPath)
{
	ShaderProgram shader;
	shader.id = glCreateProgram();
	
	GLuint vertexShader = compileShader(readFile(vertexPath), GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(readFile(fragmentPath), GL_FRAGMENT_SHADER);

	glAttachShader(shader.id, vertexShader);
	glAttachShader(shader.id, fragmentShader);
	glLinkProgram(shader.id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shader;
}

ShaderProgram ShaderProgram::createCompute(const std::string& computePath)
{
	ShaderProgram shader;

	return shader;
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(id);
}

GLuint ShaderProgram::compileShader(const std::string& src, GLenum type)
{
	GLuint shader = glCreateShader(type);

	const char* str = src.c_str();
	glShaderSource(shader, 1, &str, nullptr);
	glCompileShader(shader);

	//GLint success;
	//glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	std::string log;
	//	GLint length;
	//	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
	//	log.resize(length);

	//	glGetShaderInfoLog(shader, log.size(), nullptr, log.data());
	//	throw std::runtime_error("Could not compile shader: " + log);
	//}

	return shader;
}