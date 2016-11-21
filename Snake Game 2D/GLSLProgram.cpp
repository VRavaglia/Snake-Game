#include "GLSLProgram.h"
#include "Errors.h"
#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram() : _programID(0), _vertex_shaderID(0), _fragment_shaderID(0)
{

}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::compile_shaders(const std::string& vertex_shader_path, const std::string& fragment_shader_path)
{
	_programID = glCreateProgram();

	_vertex_shaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertex_shaderID == 0)
	{
		fatal_error("Vertex shader failed to be created!");
	}

	_fragment_shaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragment_shaderID == 0)
	{
		fatal_error("Fragment shader failed to be created!");
	}

	compile_shader(vertex_shader_path, _vertex_shaderID);
	compile_shader(fragment_shader_path, _fragment_shaderID);

}

void GLSLProgram::link_shaders()
{
	
	//Attach our shaders to our program
	glAttachShader(_programID, _vertex_shaderID);
	glAttachShader(_programID, _fragment_shaderID);

	//Link our program
	glLinkProgram(_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(_programID);
		//Don't leak shaders either.
		glDeleteShader(_vertex_shaderID);
		glDeleteShader(_fragment_shaderID);

		std::printf("%s\n", &(errorLog[0]));
		fatal_error("Shaders failed to link!");
	}

	//Always detach shaders after a successful link.
	glDetachShader(_programID, _vertex_shaderID);
	glDetachShader(_programID, _fragment_shaderID);
	glDeleteShader(_vertex_shaderID);
	glDeleteShader(_fragment_shaderID);
}

void GLSLProgram::compile_shader(const std::string& file_path, GLuint id)
{
	std::ifstream shader_file(file_path);
	if (shader_file.fail())
	{
		perror(file_path.c_str());
		fatal_error("Failed to open " + file_path);
	}

	std::string file_contents = "";
	std::string line;

	while (std::getline(shader_file, line))
	{
		file_contents += line + "\n";
	}

	shader_file.close();

	const char* contents_ptr = file_contents.c_str();

	glShaderSource(id, 1, &contents_ptr, nullptr);

	glCompileShader(id);


	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(id); // Don't leak the shader.

		std::printf("%s\n", &(errorLog[0]));
		fatal_error("Shader  " + file_path + " failed to compile");

	}

	// Shader compilation is successful.
}