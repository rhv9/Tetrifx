#pragma once
#include <glad/glad.h>

class Shader
{
public:
	Shader(GLuint program) : m_Program(program) {}
	~Shader();

	void Use();

	static Ref<Shader> CreateFromFile(const std::string& vertexSourcePath, const std::string& fragmentSourcePath);
private:
	GLuint m_Program;
};

