#include "PlayingState.h"

//Shader files
const char* PlayingState::vShader = "Shaders/shader.vert"; //Vertex shader
const char* PlayingState::fShader = "Shaders/shader.frag"; //Fragment shader

//Texture files
const char* PlayingState::grassTexturePath = "res/images/grass.png"; //Grass texture
const char* PlayingState::dirtTexturePath  = "res/images/dirt.png";  //Dirt texture


PlayingState::PlayingState(StateMachine& machine, GLWindow& glWindow, bool replace)
	: State{ machine, glWindow, replace } {

	//Camera
	camera = Camera(glm::vec3(2.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f), -90.f, 0.f, 2.5f, 0.3f);

	//Textures
	texture[0] = Texture(grassTexturePath);
	texture[0].loadTexture();
	texture[1] = Texture(dirtTexturePath);
	texture[1].loadTexture();

	//Cube
	cube = CubeGenerator(vShader, fShader);
	cube.setTexture(texture[0]);
	cube.setPosition(glm::vec3(0.f, 0.f, 0.f));
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
	cube.update(glWindow, camera, deltaTime);
}

void PlayingState::render() {
	//Clear window
	glClearColor(255.f, 255.f, 255.5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cube.render(glWindow, camera);

	glUseProgram(0);

	glWindow.swapBuffers();
}
