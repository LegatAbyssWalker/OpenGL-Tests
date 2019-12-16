#ifndef PLAYER_H
#define PLAYER_H

#include "State.h"
#include "Camera.h"
#include "GLWindow.h"
#include "MoreInfo.h"
#include "Program.h"
#include "Mesh.h"
#include "Texture.h"
#include "FileLocations.h"

#include <iostream>
#include <memory>

class Player {
	public:
		Player(glm::vec3 position);

		void updateEvents(GLWindow& glWindow);
		void update(GLfloat deltaTime);
		void render(GLWindow& glWindow);

		glm::mat4 getViewMatrix();

		const glm::vec3 getPosition();

	private:
		GLfloat deltaTime;

		Camera camera;
		GLfloat lastX = SCREEN_WIDTH / 2.f;
		GLfloat lastY = SCREEN_HEIGHT / 2.f;
		bool firstMouse = true;

		Mesh mesh;
		std::shared_ptr<Program> program;
		std::shared_ptr<Texture> texture;
};

#endif