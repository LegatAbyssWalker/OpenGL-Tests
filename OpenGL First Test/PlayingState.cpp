#include "PlayingState.h"

PlayingState::PlayingState(StateMachine& machine, GLWindow& glWindow, bool replace)
	: State{ machine, glWindow, replace } {

	//Player information
	player = std::make_unique<Player>(glm::vec3(0, 0, 0));


	//Cube
	world = std::make_unique<World>();
}

void PlayingState::updateEvents() {
	//Get + Handle user input events
	glfwPollEvents();

	player->updateEvents(glWindow);
}

void PlayingState::update() {
	/*-------------------------------------------------------------------------------------------------------------------*/
	//Delta time
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;


	/*-------------------------------------------------------------------------------------------------------------------*/
	//Player updates
	player->update(deltaTime);

	/*-------------------------------------------------------------------------------------------------------------------*/
	//World updates
	world->update();
}

void PlayingState::render() {
	//Clear window
	glClearColor(0.5f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	world->render(glWindow, player->getViewMatrix());

	player->render(glWindow);

	glUseProgram(0);

	glWindow.swapBuffers();
}