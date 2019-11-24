#ifndef SHADER_H
#define SHADER_H

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader {
	public:
		Shader() = default;
		Shader(Shader&& shader);
		Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

		void useShader();

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;

		void setVec2(const std::string& name, const glm::vec2& value) const;
		void setVec2(const std::string& name, GLfloat x, GLfloat y) const;

		void setVec3(const std::string& name, const glm::vec3& value) const;
		void setVec3(const std::string& name, GLfloat x, GLfloat y, GLfloat z) const;

		void setVec4(const std::string& name, const glm::vec4& value) const;
		void setVec4(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;

		void setMat2(const std::string& name, const glm::mat2& mat) const;
		void setMat3(const std::string& name, const glm::mat3& mat) const;
		void setMat4(const std::string& name, const glm::mat4& mat) const;

	private:
		GLuint shaderID, uniformModel, uniformProjection, uniformView;

		void checkCompileErrors(GLuint shaderType, std::string type);
};

#endif