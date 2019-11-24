#ifndef CUBEGENERATOR_H
#define CUBEGENERATOR_H

#include "State.h"
#include "Mesh.h"
#include "Program.h"
#include "Texture.h"
#include "Camera.h"
#include "GLWindow.h"

#include <iostream>
#include <vector>

class CubeGenerator {
	public:
		CubeGenerator();

		void setTexture(std::shared_ptr<Texture> texture);
		void setPosition(glm::vec3 position = glm::vec3(0.f, 0.f, 0.f));

		void update(GLWindow& glWindow, Camera& camera, GLfloat deltaTime);
		void render(GLWindow& glWindow, Camera& camera);

		glm::vec3 getPosition();

	private:
		Mesh mesh;
		std::shared_ptr<Program> program;
		std::shared_ptr<Texture> texture;

		glm::vec3 position;

		std::vector<GLuint> vertices;
};

#endif