#include "CubeGenerator.h"

CubeGenerator::CubeGenerator(const char* vShader, const char* fShader) {
	std::vector<GLfloat> vertices{
		//   X   Y   Z   U     V  
		//1
			-1, -1,  1, 0.25, 0.34,
			-1, -1, -1, 0.25, 0.66,
			-1,  1,  1, 0.00, 0.34,
			-1,  1,  1, 0.00, 0.34,
			-1,  1, -1, 0.00, 0.66,
			-1, -1, -1, 0.25, 0.66,

		//2
			-1, -1, -1, 0.25, 0.66,
			-1, -1,  1, 0.25, 0.34,
			 1, -1,  1, 0.50, 0.34,
			 1, -1,  1, 0.50, 0.34,
			 1, -1, -1, 0.50, 0.66,
			-1, -1, -1, 0.25, 0.66,

		//3
			-1,  1, -1, 0.25, 1.00,
			-1, -1, -1, 0.25, 0.66,
			 1, -1, -1, 0.50, 0.66,
			 1, -1, -1, 0.50, 0.66,
			 1,  1, -1, 0.50, 1.00,
			-1,  1, -1, 0.25, 1.00,

		//4
			-1,  1,  1, 0.25, 0.00,
			-1, -1,  1, 0.25, 0.34,
			 1, -1,  1, 0.50, 0.34,
			 1, -1,  1, 0.50, 0.34,
			 1,  1,  1, 0.50, 0.00,
			-1,  1,  1, 0.25, 0.00,

		//5
			 1, -1,  1, 0.50, 0.34,
			 1, -1, -1, 0.50, 0.66,
			 1,  1,  1, 0.75, 0.34,
			 1,  1,  1, 0.75, 0.34,
			 1,  1, -1, 0.75, 0.66,
			 1, -1, -1, 0.50, 0.66,

		//6
			-1,  1, -1, 1.00, 0.66,
			-1,  1,  1, 1.00, 0.34,
			 1,  1,  1, 0.75, 0.34,
			 1,  1,  1, 0.75, 0.34,
			 1,  1, -1, 0.75, 0.66,
			-1,  1, -1, 1.00, 0.66
	};

	mesh.createMesh(vertices);
	shader.createFromFiles(vShader, fShader);
}

void CubeGenerator::setTexture(const Texture& texture) {
	this->texture = texture;
}

void CubeGenerator::setPosition(glm::vec3 position) {
	this->position = position;
}

void CubeGenerator::update(GLWindow& glWindow, Camera& camera, GLfloat deltaTime) {
	camera.processKeyboard(glWindow.getKeys(), deltaTime);
	camera.processMouseMovement(glWindow.getXChange(), glWindow.getYChange());
}

void CubeGenerator::render(Camera& camera, const glm::mat4& projection) {
	shader.useShader();
	uniformModel = shader.getModelLocation();
	uniformProjection = shader.getProjectionLocation();
	uniformView = shader.getViewLocation();

	glm::mat4 model(1.f);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

	//Camera matrix
	glm::mat4 view = camera.calculateViewMatrix();

	//Uniform
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
	//Textures assignment
	texture.useTexture();

	//Rendering
	mesh.renderMesh();
}

glm::vec3 CubeGenerator::getPosition() {
	return glm::vec3(position);
}
