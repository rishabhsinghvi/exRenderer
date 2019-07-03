#ifndef SHADER_H
#define SHADER_H

#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<unordered_map>

#include<glm/mat3x3.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/type_ptr.hpp>


class Shader
{
public:
private: 
	unsigned int shader_id;

public:
	Shader() = delete;

	Shader(const std::string& vertexPath, const std::string& fragmentPath);

	Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geoPath);

	~Shader();

	void bind() const;

	void unbind() const;

	// setting a uniform to a shader currently not in use will bind the shader first

	void setUniformFloat(const std::string& uniformName, const std::vector<float>& uniformArgs) const;

	void setUniformInt(const std::string& uniformName, const std::vector<int>& uniformArgs) const;

	void setUniformBool(const std::string& uniformName, bool uniformArg) const;

	
	void setUniformMatrix4(const std::string& uniformName, const glm::mat4& matrix) const;

	void setUniformMatrix3(const std::string & uniformName,const  glm::mat3& matrix) const;
	

private:

	void createShaderProgram(const char* vertexSource, const char* fragSource);
	void createShaderProgram(const char* vertexSource, const char* fragSource, const char* geoSource);

	void getErrors(unsigned int s_id);

	void checkLinkStatus();
};


#endif