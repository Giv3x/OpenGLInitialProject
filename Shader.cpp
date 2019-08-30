#include "Shader.h"

#include <iostream>
#include <fstream>

void Shader::initShader(const std::string& fileName) {
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(loadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(loadShader(fileName + ".txt"), GL_FRAGMENT_SHADER);

	for (int i = 0; i < NUM_SHADERS; i++) {
		glAttachShader(m_program, m_shaders[i]);
	}

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	glLinkProgram(m_program);
	checkShaderError(m_program, GL_LINK_STATUS, true, "Program Linking failed");

	glValidateProgram(m_program);
	checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Invalid Shader Program");
}

Shader::~Shader() {
}

void Shader::free() {
	for (int i = 0; i < NUM_SHADERS; i++) {
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);
}

void Shader::getUniformLocation(GLchar*name) {
	uniforms[name] = glGetUniformLocation(m_program, name);
}

void Shader::getUniformLocations(GLchar** names, int size) {
	for (int i = 0; i < 4; i++) {
		uniforms[names[i]] = glGetUniformLocation(m_program, names[i]);
	}
}

void Shader::bindUniform(GLchar* name, const glm::vec4& data) {
	if (uniforms.find(name) == uniforms.end())
		this->getUniformLocation(name);
	glUniform4fv(uniforms[name], 1, &data[0]);
}

void Shader::bindUniform(GLchar* name, const glm::vec3& data) {
	if (uniforms.find(name) == uniforms.end())
		this->getUniformLocation(name);
	glUniform3fv(uniforms[name], 1, &data[0]);
}

void Shader::bindUniform(GLchar* name, float number) {
	if (uniforms.find(name) == uniforms.end())
		this->getUniformLocation(name);
	glUniform1f(uniforms[name], number);
}

void Shader::bindUniform(GLchar* name, const glm::mat4& matrix) {
	if (uniforms.find(name) == uniforms.end())
		this->getUniformLocation(name);
	glUniformMatrix4fv(uniforms[name], 1, false, &matrix[0][0]);
}

void Shader::Bind() {
	glUseProgram(m_program);
}

void Shader::Stop() {
	glUseProgram(0);
}

std::string Shader::loadShader(const std::string& fileName) {
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
	GLint success = 0;
	GLchar error[1024] = { 0 };
	
	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else 
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

GLuint Shader::CreateShader(const std::string& shaderCode, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);

	if(shader == 0)
		std::cerr << "Error compiling shader type " << shaderType << std::endl;

	const GLchar* p[1];
	GLint lengths[1];

	p[0] = shaderCode.c_str();
	lengths[0] = shaderCode.size();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	checkShaderError(shader, GL_COMPILE_STATUS, false, "Shader Compilation failed");

	return shader;
}