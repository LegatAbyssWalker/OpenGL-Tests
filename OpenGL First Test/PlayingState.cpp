#include "PlayingState.h"

//Texture files
static const char* grassTexturePath = "res/images/grass.png"; //Grass texture
static const char* dirtTexturePath  = "res/images/dirt.png";  //Dirt texture

PlayingState::PlayingState(StateMachine& machine, GLWindow& glWindow, bool replace)
	: State{ machine, glWindow, replace } {

	//Camera
	camera = Camera(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f), -90.f, 0.f, 2.5f, 0.3f);

	//Cube
	cubeVector.resize(10);
	for (GLsizei x = 0; x < cubeVector.size(); x++) {
		cubeVector[x].setTexture(Texture::get(grassTexturePath));
		cubeVector[x].setPosition(glm::vec3(x, 0.f, 0.f));
	}
}

void PlayingState::updateEvents() {
	//Get + Handle user input events
	glfwPollEvents();
}

void PlayingState::update() {
	/*-------------------------------------------------------------------------------------------------------------------*/
	//Delta time
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	/*-------------------------------------------------------------------------------------------------------------------*/
	//Cube 
	for (auto& cube : cubeVector) { cube.update(glWindow, camera, deltaTime); }
}

void PlayingState::render() {
	//Clear window
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& cube : cubeVector) { cube.render(glWindow, camera); }

	glUseProgram(0);

	glWindow.swapBuffers();
}