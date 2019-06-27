#include "Shader.h"
#include "glad/glad.h"
#include<iostream>
#include<cassert>


Shader::Shader(const std::string& vertexPath, const std::string& fragPath): shader_id(0)
{
	std::ifstream vertexFile(vertexPath);
	std::ifstream fragFile(fragPath);

	if (!vertexFile.is_open() || !fragFile.is_open())
	{
		std::cout << "========ERROR==========\n";
		std::cout << "Unable to open one or more shader files!\n";
		exit(0);
	}

	std::stringstream v_buffer;
	std::stringstream f_buffer;

	v_buffer << vertexFile.rdbuf();
	f_buffer << fragFile.rdbuf();

	vertexFile.close();
	fragFile.close();


	createShaderProgram(v_buffer.str().c_str(), f_buffer.str().c_str());
}

Shader::Shader(const std::string & vertexPath, const std::string & fragPath, const std::string & geoPath): shader_id(0)
{
	std::ifstream vertexFile(vertexPath);
	std::ifstream fragFile(fragPath);
	std::ifstream geoFile(geoPath);

	if (!vertexFile.is_open() || !fragFile.is_open() || !geoFile.is_open())
	{
		std::cout << "========ERROR==========\n";
		std::cout << "Unable to open one or more shader files!\n";
		exit(0);
	}

	std::stringstream v_buffer;
	std::stringstream f_buffer;
	std::stringstream g_buffer;

	v_buffer << vertexFile.rdbuf();
	f_buffer << fragFile.rdbuf();
	g_buffer << geoFile.rdbuf();


	vertexFile.close();
	fragFile.close();
	geoFile.close();

	createShaderProgram(v_buffer.str().c_str(), f_buffer.str().c_str(), g_buffer.str().c_str());
}

Shader::~Shader()
{
	glUseProgram(0);
	glDeleteProgram(shader_id);
}

void Shader::bind() const
{
	glUseProgram(shader_id);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

void Shader::setUniformFloat(const std::string & uniformName, const std::vector<float>& uniformArgs, unsigned int numArgs) const
{
	bind();
	assert(numArgs >= 1 && numArgs <= 4);
	auto loc = glGetUniformLocation(shader_id, uniformName.c_str());

	switch (numArgs)
	{
	case 1:
		glUniform1f(loc, uniformArgs[0]);
		return;
	case 2:
		glUniform2f(loc, uniformArgs[0], uniformArgs[1]);
		return;
	case 3:
		glUniform3f(loc, uniformArgs[0], uniformArgs[1], uniformArgs[2]);
		return;
	case 4:
		glUniform4f(loc, uniformArgs[0], uniformArgs[1], uniformArgs[2], uniformArgs[3]);
		return;
	}
	assert(false);
}

void Shader::setUniformInt(const std::string & uniformName, const std::vector<float>& uniformArgs, unsigned int numArgs) const
{
	bind();
	assert(numArgs >= 1 && numArgs <= 4);
	auto loc = glGetUniformLocation(shader_id, uniformName.c_str());

	switch (numArgs)
	{
	case 1:
		glUniform1i(loc, uniformArgs[0]);
		return;
	case 2:
		glUniform2i(loc, uniformArgs[0], uniformArgs[1]);
		return;
	case 3:
		glUniform3i(loc, uniformArgs[0], uniformArgs[1], uniformArgs[2]);
		return;
	case 4:
		glUniform4i(loc, uniformArgs[0], uniformArgs[1], uniformArgs[2], uniformArgs[3]);
		return;
	}
	assert(false);
}

void Shader::setUniformBool(const std::string & uniformName, bool uniformArg) const
{
	bind();
	auto loc = glGetUniformLocation(shader_id, uniformName.c_str());
	glUniform1i(loc, static_cast<int>(uniformArg));
}


void Shader::setUniformMatrix4(const std::string & uniformName, const glm::mat4& matrix) const
{
	bind();
	auto loc = glGetUniformLocation(shader_id, uniformName.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniformMatrix3(const std::string & uniformName, const glm::mat3& matrix) const
{
	bind();
	auto loc = glGetUniformLocation(shader_id, uniformName.c_str());
	glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}


void Shader::createShaderProgram(const char* vertexSource, const char* fragSource)
{
	unsigned int vertexShader, fragmentShader;
	
	// Create vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	// Check for compilation errors
	getErrors(vertexShader);

	// Create fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragSource, nullptr);
	glCompileShader(fragmentShader);

	// Check for compilation errors
	getErrors(fragmentShader);

	shader_id = glCreateProgram();

	glAttachShader(shader_id, vertexShader);
	glAttachShader(shader_id, fragmentShader);

	glLinkProgram(shader_id);
	checkLinkStatus();

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::createShaderProgram(const char* vertexSource, const char* fragSource, const char* geoSource)
{
	unsigned int vertexShader, fragmentShader, geoShader;

	// Create vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	// Check for compilation errors
	getErrors(vertexShader);

	// Create fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragSource, nullptr);
	glCompileShader(fragmentShader);

	// Check for compilation errors
	getErrors(fragmentShader);

	// Create geometry shader
	geoShader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geoShader, 1, &geoSource, nullptr);
	glCompileShader(geoShader);

	// Check for compilation errors
	getErrors(geoShader);

	shader_id = glCreateProgram();

	glAttachShader(shader_id, vertexShader);
	glAttachShader(shader_id, fragmentShader);
	glAttachShader(shader_id, geoShader);

	glLinkProgram(shader_id);
	checkLinkStatus();

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(geoShader);
	
}



void Shader::getErrors(unsigned int s_id)
{
	int res;

	glGetShaderiv(s_id, GL_COMPILE_STATUS, &res);
	if (!res)
	{
		char errMsg[1000];
		glGetShaderInfoLog(s_id, 1000, nullptr, errMsg);
		std::cout << "============COMPILATION ERROR================\n";
		std::cout << errMsg << "\n";
		std::cin.get();
	}

}

void Shader::checkLinkStatus()
{
	int res;

	glValidateProgram(shader_id);
	glGetProgramiv(shader_id, GL_LINK_STATUS, &res);

	if (!res)
	{
		char errMsg[1000];
		glGetShaderInfoLog(shader_id, 1000, nullptr, errMsg);
		std::cout << "========SHADER ERROR=============\n";
		std::cout << "Failed to link program.\n";
		std::cout << errMsg << "\n";
		std::cin.get();
		exit(0);
	}
}

