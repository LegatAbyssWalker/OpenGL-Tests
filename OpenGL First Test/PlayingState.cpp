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

	//Cube positionings
	cubePositionVector = { 
		//Row 1
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(2.f, 0.f, 0.f),
		glm::vec3(3.f, 0.f, 0.f),
		glm::vec3(4.f, 0.f, 0.f),

		//Row 2
		glm::vec3(0.f, 1.f, 0.f),
		glm::vec3(1.f, 1.f, 0.f),
		glm::vec3(2.f, 1.f, 0.f),
		glm::vec3(3.f, 1.f, 0.f),
		glm::vec3(4.f, 1.f, 0.f),

		//Row 3
		glm::vec3(0.f, 2.f, 0.f),
		glm::vec3(1.f, 2.f, 0.f),
		glm::vec3(2.f, 2.f, 0.f),
		glm::vec3(3.f, 2.f, 0.f),
		glm::vec3(4.f, 2.f, 0.f),

		//Row 4
		glm::vec3(0.f, 3.f, 0.f),
		glm::vec3(1.f, 3.f, 0.f),
		glm::vec3(2.f, 3.f, 0.f),
		glm::vec3(3.f, 3.f, 0.f),
		glm::vec3(4.f, 3.f, 0.f),

		//Row 5
		glm::vec3(0.f, 4.f, 0.f),
		glm::vec3(1.f, 4.f, 0.f),
		glm::vec3(2.f, 4.f, 0.f),
		glm::vec3(3.f, 4.f, 0.f),
		glm::vec3(4.f, 4.f, 0.f),
	}; 
}

void PlayingState::createMesh() {
	std::vector<GLuint> indices{
		//Top
		2, 6, 7,
		2, 3, 7,

		//Bottom
		0, 4, 5,
		0, 1, 5,

		//Left
		0, 2, 6,
		0, 4, 6,

		//Right
		1, 3, 7,
		1, 5, 7,

		//Front
		0, 2, 3,
		0, 1, 3,

		//Back
		4, 6, 7,
		4, 5, 7
	};
	
	std::vector<GLfloat> vertices{
	//   X   Y   Z  U  V  
		-1, -1,  1, 0, 0, //0 
		 1, -1,  1, 0, 1, //1
		-1,  1,  1, 1, 0, //2
		 1,  1,  1, 1, 1, //3
		-1, -1, -1, 0, 0, //4
		 1, -1, -1, 0, 1, //5
		-1,  1, -1, 1, 0, //6
		 1,  1, -1, 1, 1  //7
	};

	for (GLsizei x = 0; x < 1; x++) {
		meshVector.emplace_back(new Mesh());
		meshVector[x]->createMesh(vertices, indices);
	}
}

void PlayingState::createShaders() {
	for (GLsizei x = 0; x < 1; x++) {
		shaderVector.emplace_back(new Shader());
		shaderVector[x]->createFromFiles(vShader, fShader);
	}
}

void PlayingState::updateEvents() {
	//Get + Handle user input events
	glfwPollEvents();
}

void PlayingState::update() {
	//Delta time
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	camera.processKeyboard(glWindow.getKeys(), deltaTime);
	camera.processMouseMovement(glWindow.getXChange(), glWindow.getYChange());
}

void PlayingState::render() {
	//Clear window
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	shaderVector[0]->useShader();
	uniformModel      = shaderVector[0]->getModelLocation();
	uniformProjection = shaderVector[0]->getProjectionLocation();
	uniformView       = shaderVector[0]->getViewLocation();


	for (GLsizei x = 0; x < meshVector.size(); x++) {
		//Model information
		glm::mat4 model(1.f);
		model = glm::translate(model, cubePositionVector[x]);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

		//Camera matrix
		glm::mat4 view = camera.calculateViewMatrix();

		//Uniform
		glUniformMatrix4fv(uniformModel,      1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView,       1, GL_FALSE, glm::value_ptr(view));

		//Textures
		texture[0].useTexture();

		//Rendering
		meshVector[x]->renderMesh();
	}

	glUseProgram(0);

	glWindow.swapBuffers();
}
