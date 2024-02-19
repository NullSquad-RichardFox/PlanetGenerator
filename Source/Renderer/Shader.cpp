#include "epch.h"
#include "Shader.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/gtc/type_ptr.hpp"


UShader::UShader(const std::string& shaderPath)
{
	std::string src = ReadFile(shaderPath);
	std::unordered_map<GLuint, std::string> shaderData = ParseShader(src);

	CreateProgram(shaderData[GL_VERTEX_SHADER].c_str(), shaderData[GL_FRAGMENT_SHADER].c_str());
}

UShader::UShader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	CreateProgram(vertexSrc.c_str(), fragmentSrc.c_str());
}

UShader::~UShader()
{
	glDeleteProgram(ShaderID);
}

void UShader::Bind() const
{
	glUseProgram(ShaderID);
}

void UShader::Unbind() const
{
	glUseProgram(0);
}

void UShader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ShaderID, name.c_str()), (int)value);
}

void UShader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ShaderID, name.c_str()), value);
}

void UShader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ShaderID, name.c_str()), value);
}

void UShader::SetMat4(const std::string& name, const glm::mat4& matrix) const
{
	GLuint loc = glGetUniformLocation(ShaderID, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void UShader::SetFloat3(const std::string& name, glm::vec3 value) const
{
	GLuint loc = glGetUniformLocation(ShaderID, name.c_str());
	glUniform3f(loc, value.x, value.y, value.z);
}

std::string UShader::ReadFile(const std::string& path)
{
	std::ifstream file(path, std::ios::in);
	LOG("Path: {0}", path);
	ASSERT(file, "Couldn't open shader file!");

	file.seekg(0, std::ios::end); // sets the last line as the current line
	size_t length = file.tellg(); // tells the line pos

	ASSERT(length != -1, "Shader file is empty!");

	std::string src;
	src.resize(length);
	file.seekg(0, std::ios::beg); // resets
	file.read(&src[0], length); // coppies the data

	return src;
}

std::unordered_map<GLuint, std::string> UShader::ParseShader(const std::string& file)
{
	std::string typeToken = "#type ";
	size_t typePos = file.find(typeToken, 0);

	std::unordered_map<GLuint, std::string> shaderData;

	ASSERT(typePos != std::string::npos, "Syntax error: shader type not specified!");
	while (typePos != std::string::npos)
	{
		size_t typePosEnd = file.find_first_of('\n', typePos);
		std::string typeSrc = file.substr(typePos + typeToken.size(), typePosEnd - typeToken.size() - typePos);

		GLenum type;
		if (typeSrc == "vertex")
		{
			type = GL_VERTEX_SHADER;
		}
		else if (typeSrc == "fragment")
		{
			type = GL_FRAGMENT_SHADER;
		}
		else
		{
			ASSERT(false, "Syntax error: wrong shader type!");
		}

		size_t shaderSrcStart = file.find_first_not_of('\n', typePosEnd);
		ASSERT(shaderSrcStart != std::string::npos, "Syntax error: shader code missing!");

		typePos = file.find(typeToken, shaderSrcStart);
		shaderData[type] = typePos == std::string::npos ? file.substr(shaderSrcStart) : file.substr(shaderSrcStart, typePos - shaderSrcStart);
	}

	ASSERT(shaderData.size() == 2, "IShader file doesn't contain both shade types!");

	return shaderData;
}

void UShader::CreateProgram(const char* vertexSrc, const char* fragmentSrc)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	const GLchar* source = vertexSrc;
	glShaderSource(vertexShader, 1, &source, 0);

	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLenght = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLenght);

		std::vector<GLchar> infoLog(maxLenght);
		glGetShaderInfoLog(vertexShader, maxLenght, &maxLenght, &infoLog[0]);

		glDeleteShader(vertexShader);

		LOG_ERROR("{0}", infoLog.data());
		ASSERT(false, "Vertex shader did not compile!");

		return;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	source = (const GLchar*)fragmentSrc;
	glShaderSource(fragmentShader, 1, &source, 0);

	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLenght = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLenght);

		std::vector<GLchar> infoLog(maxLenght);
		glGetShaderInfoLog(fragmentShader, maxLenght, &maxLenght, &infoLog[0]);

		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);

		LOG_ERROR("{0}", infoLog.data());
		ASSERT(false, "Fragment shader did not compile!");

		return;
	}

	ShaderID = glCreateProgram();

	glAttachShader(ShaderID, vertexShader);
	glAttachShader(ShaderID, fragmentShader);

	glLinkProgram(ShaderID);

	GLint isLinked = 0;
	glGetProgramiv(ShaderID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLenght = 0;
		glGetProgramiv(ShaderID, GL_INFO_LOG_LENGTH, &maxLenght);

		std::vector<GLchar> infoLog(maxLenght);
		glGetProgramInfoLog(ShaderID, maxLenght, &maxLenght, &infoLog[0]);

		glDeleteProgram(ShaderID);

		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);

		LOG_ERROR("{0}", infoLog.data());
		ASSERT(false, "Shader did not compile!");

		return;
	}

	glDetachShader(ShaderID, vertexShader);
	glDetachShader(ShaderID, fragmentShader);
}
