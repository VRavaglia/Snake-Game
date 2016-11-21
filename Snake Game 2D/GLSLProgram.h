#pragma once
#include <string>
#include <GL/glew.h>

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compile_shaders(const std::string& vertex_shader_path, const std::string& fragment_shader_path);

	void link_shaders();

private:
	void compile_shader(const std::string& file_path, GLuint id);

	GLuint _programID;

	GLuint _vertex_shaderID;
	GLuint _fragment_shaderID;
};

