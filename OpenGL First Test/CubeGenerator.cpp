#include "CubeGenerator.h"

//Shader files
const char* vShader = "Shaders/shader.vert"; //Vertex program
const char* fShader = "Shaders/shader.frag"; //Fragment program

CubeGenerator::CubeGenerator() 
	: mesh() {
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
	program = Program::get(vShader, fShader);
}

void CubeGenerator::setTexture(std::shared_ptr<Texture> texture) {
	this->texture = texture;
}

void CubeGenerator::setPosition(glm::vec3 position) {
	this->position = position;
}

void CubeGenerator::update(GLWindow& glWindow, Camera& camera, GLfloat deltaTime) {
	camera.processKeyboard(glWindow.getKeys(), deltaTime);
	camera.processMouseMovement(glWindow.getXChange(), glWindow.getYChange());
}

void CubeGenerator::render(GLWindow& glWindow, Camera& camera) {
	program->useProgram();
	 
	glm::mat4 model(1.f);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

	//Camera matrix
	glm::mat4 view = camera.calculateViewMatrix();

	//Projection
	glm::mat4 projection = glm::perspective(glm::radians(45.f), (GLfloat)glWindow.getBufferWidth() / glWindow.getBufferHeight(), 0.1f, 100.f);

	//Uniform
	program->setMat4("model", model);
	program->setMat4("view", view);
	program->setMat4("projection", projection);

	//Textures assignment
	texture->useTexture();

	//Rendering
	mesh.renderMesh();
}

glm::vec3 CubeGenerator::getPosition() {
	return glm::vec3(position);
}
