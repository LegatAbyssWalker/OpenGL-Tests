#include "Player.h"

Player::Player(glm::vec3 position) {
	
	std::vector<GLfloat> crosshairVertices {
		//   X      Y   Z  U  V
		// Horizontal
			-1.0,  0.2, 0, 0, 0,
			-1.0, -0.2, 0, 0, 0,
			 1.0,  0.2, 0, 0, 0,
			 1.0,  0.2, 0, 0, 0,
			-1.0, -0.2, 0, 0, 0,
			 1.0, -0.2, 0, 0, 0,

		//Verticle
			 0.2,  1.0, 0, 0, 0,
			-0.2,  1.0, 0, 0, 0,
			-0.2, -1.0, 0, 0, 0,
			-0.2, -1.0, 0, 0, 0,
			 0.2, -1.0, 0, 0, 0,
			 0.2,  1.0, 0, 0, 0
	};

	mesh.createMesh(crosshairVertices);
	program = Program::get(VERTEX_SHADER, FRAGMENT_SHADER);

	//Camera/
	camera = Camera(position, glm::vec3(0.f, 1.f, 0.f), -90.f, 0.f, 2.5f, 0.3f);

}

void Player::updateEvents(GLWindow& glWindow) {
	//Camera event updates
	camera.processKeyboard(glWindow.getKeys(), deltaTime);
	camera.processMouseMovement(glWindow.getXChange(), glWindow.getYChange());
}

void Player::update(GLfloat deltaTime) {
	this->deltaTime = deltaTime;
}

void Player::render(GLWindow& glWindow) {
	program->useProgram();

	//Model matrix
	glm::mat4 model(1.f);
	model = glm::translate(model, camera.getPosition());
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));

	//Uniforms
	program->setMat4("model", model);

	//Rendering
	mesh.renderMesh();
}

glm::mat4 Player::getViewMatrix() {
	return camera.calculateViewMatrix();
}
