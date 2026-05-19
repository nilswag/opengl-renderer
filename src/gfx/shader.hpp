#pragma once
#include <string>
#include <glad/gl.h>

class ShaderProgram
{
public:
	static ShaderProgram createGraphics(const std::string& vertexPath, const std::string& fragmentPath);
	static ShaderProgram createCompute(const std::string& computePath);

	ShaderProgram(ShaderProgram&&) = default;
	ShaderProgram& operator=(ShaderProgram&&) = default;
	~ShaderProgram();

	inline GLuint get() const { return id; }
	inline void use() const { glUseProgram(id); }

private:
	static GLuint compileShader(const std::string& src, GLenum type);

	ShaderProgram() = default;
	ShaderProgram(const ShaderProgram&) = default;
	ShaderProgram& operator=(const ShaderProgram&) = default;

	GLuint id;
};
