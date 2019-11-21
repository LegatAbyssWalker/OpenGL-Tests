#include "PlayingState.h"

//Shader files
const char* PlayingState::vShader = "Shaders/shader.vert"; //Vertex shader
const char* PlayingState::fShader = "Shaders/shader.frag"; //Fragment shader

//Texture files
const char* PlayingState::grassTexturePath = "res/images/grass.png"; //Grass texture
const char* PlayingState::dirtTexturePath  = "res/images/dirt.png";  //Dirt texture


PlayingState::PlayingState(StateMachine& machine, GLWindow& glWindow, bool replace)
	: State{ machine, glWindow, replace } {


	//Objects/Shaders
	createMesh();
	createShaders();

	//Camera
	camera = Camera(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f), -90.f, 0.f, 2.5f, 0.3f);

	//Textures
	texture[0] = Texture(grassTexturePath);
	texture[0].loadTexture();
	texture[1] = Texture(dirtTexturePath);
	texture[1].loadTexture();

	//Projection
	projection = glm::perspective(glm::radians(45.f), (GLfloat)glWindow.getBufferWidth() / glWindow.getBufferHeight(), 0.1f, 100.f);

	//Cube
	cube = CubeGenerator(vShader, fShader);
}

void PlayingState::createMesh() {
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


	for (GLsizei x = 0; x < 8; x++) {
		meshVector.push_back(new Mesh());
		meshVector[x]->createMesh(vertices);
	}
}

void PlayingState::createShaders() {
	for (GLsizei x = 0; x < 1; x++) {
		shaderVector.push_back(new Shader());
		shaderVector[x]->createFromFiles(vShader, fShader);
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

	camera.processKeyboard(glWindow.getKeys(), deltaTime);
	camera.processMouseMovement(glWindow.getXChange(), glWindow.getYChange());


	/*-------------------------------------------------------------------------------------------------------------------*/
	//Cube 
	cube.setTexture(texture[0]);
	cube.setPosition(glm::vec3(0.f, 0.f, 0.f));
}

void PlayingState::render() {
	//Clear window
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cube.render(camera, projection);

	glUseProgram(0);

	glWindow.swapBuffers();
}
