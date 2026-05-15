#include <string>
#include <stdexcept>
#include <glad/gl.h>
#include "shader.hpp"
#include "../util/io.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	program = glCreateProgram();
	GLuint vertexShader = compileShader(readFile(vertexPath), GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(readFile(fragmentPath), GL_FRAGMENT_SHADER);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(program);
}

GLuint Shader::compileShader(const std::string& src, GLenum type)
{
	GLuint shader = glCreateShader(type);

	const char* str = src.c_str();
	glShaderSource(shader, 1, &str, nullptr);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::string log;
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		log.resize(length);

		glGetShaderInfoLog(shader, log.size(), nullptr, log.data());
		throw std::runtime_error("Could not compile shader: " + log);
	}

	return shader;
}