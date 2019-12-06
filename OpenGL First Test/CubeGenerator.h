#ifndef CUBEGENERATOR_H
#define CUBEGENERATOR_H

#include "State.h"
#include "Mesh.h"
#include "Program.h"
#include "Texture.h"
#include "GLWindow.h"
#include "FileLocations.h"

#include <iostream>
#include <vector>

class CubeGenerator {
	public:
		CubeGenerator();

		void setTexture(std::shared_ptr<Texture> texture);
		void setPosition(glm::vec3 position = glm::vec3(0.f, 0.f, 0.f));

		void render(GLWindow& glWindow, const glm::mat4 viewMatrix);

		glm::vec3 getPosition();

	private:
		Mesh mesh;
		std::shared_ptr<Program> program;
		std::shared_ptr<Texture> texture;

		glm::vec3 position;
		glm::vec3 scaleValue;

		std::vector<GLuint> vertices;
};

#endif