#ifndef CUBEGENERATOR_H
#define CUBEGENERATOR_H

#include "State.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

#include <iostream>
#include <vector>

class CubeGenerator {
	public:
		CubeGenerator() = default;
		CubeGenerator(static const char* vShader, static const char* fShader);
		
		void setTexture(const Texture& texture);
		void setPosition(glm::vec3 position);
		void render(Camera& camera, const glm::mat4& projection);

	private:
		Mesh mesh;
		Shader shader;
		Texture texture;

		glm::vec3 position;

		std::vector<GLuint> vertices;

		//Uniform variables
		GLuint uniformModel = 0, uniformProjection = 0, uniformView = 0;
};

#endif