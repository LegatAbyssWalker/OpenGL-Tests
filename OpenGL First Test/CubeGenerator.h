#ifndef CUBEGENERATOR_H
#define CUBEGENERATOR_H

#include "State.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "GLWindow.h"

#include <iostream>
#include <vector>

class CubeGenerator {
	public:
		CubeGenerator() = default;
		CubeGenerator(const char* vShader, const char* fShader);
		
		void setTexture(const Texture& texture);
		void setPosition(glm::vec3 position = glm::vec3(0.f, 0.f, 0.f));

		void update(GLWindow& glWindow, Camera& camera, GLfloat deltaTime);
		void render(GLWindow& glWindow, Camera& camera);

		glm::vec3 getPosition();

	private:
		//Shaders
		static const char* vShader; //Vertex shader
		static const char* fShader; //Fragment shader

		Mesh mesh;
		Shader shader;
		Texture texture;

		glm::vec3 position; 

		std::vector<GLuint> vertices;
};

#endif