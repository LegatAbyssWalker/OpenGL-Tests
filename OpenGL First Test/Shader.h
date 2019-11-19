#ifndef SHADER_H
#define SHADER_H

#include "GL/glew.h"

#include <iostream>
#include <fstream>
#include <string>


class Shader {
	public:
		Shader();
		~Shader();

		void createFromString(const char* vertexCode, const char* fragmentCode);
		void createFromFiles(const char* vertexLocation, const char* fragmentLocation);

		std::string readFile(const char* fileLocation);

		GLuint getModelLocation() { return uniformModel; }
		GLuint getProjectionLocation() { return uniformProjection; }
		GLuint getViewLocation() { return  uniformView; }

		void useShader();
		void clearShader();

	private:
		GLuint shaderID, uniformModel, uniformProjection, uniformView;

		void compileShader(const char* vertexCode, const char* fragmentCode);
		void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

#endif