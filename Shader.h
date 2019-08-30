#pragma once
#include <string>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <map>
#include <vector>

class Shader {
public:
	Shader() {}

	void initShader(const std::string& fileName);
	void Bind();
	void Stop();
	void free();
	void getUniformLocation(GLchar*name);
	void getUniformLocations(GLchar** names, int size);
	void bindUniform(GLchar* name, const glm::mat4& matrix);
	void bindUniform(GLchar* name, const glm::vec4& data);
	void bindUniform(GLchar* name, const glm::vec3& data);
	void bindUniform(GLchar* name, float number);

	virtual ~Shader();
protected:

private:
	static const unsigned int NUM_SHADERS = 2;

	std::string loadShader(const std::string& fileName);
	GLuint CreateShader(const std::string& shader, GLenum shaderType);
	void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

	GLuint m_program;
	GLuint m_uboHandle = -1;
	GLuint m_shaders[NUM_SHADERS];
	std::map<GLchar*, GLint> uniforms;
};