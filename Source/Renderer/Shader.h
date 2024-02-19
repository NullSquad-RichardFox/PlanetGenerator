#pragma once


typedef unsigned int GLuint;

class UShader
{
public:
	UShader(const std::string& shaderPath);
	UShader(const std::string& vertexSrc, const std::string& fragmentSrc);
	~UShader();

	void Bind() const;
	void Unbind() const;

	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetMat4(const std::string& name, const glm::mat4& matrix) const;
	void SetFloat3(const std::string& name, glm::vec3 value) const;

private:
	std::string ReadFile(const std::string& path);
	std::unordered_map<GLuint, std::string> ParseShader(const std::string& file);
	void CreateProgram(const char* vertexSrc, const char* fragmentSrc);

	uint32_t ShaderID;
};