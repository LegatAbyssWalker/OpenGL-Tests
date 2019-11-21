#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "State.h"
#include "StateMachine.h"
class StateMachine;

#include <iostream>
#include <fstream>
#include <array>
#include <memory>
#include <vector>
#include <array>

#include "GLWindow.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "MoreInfo.h"
#include "Texture.h"

#include "CubeGenerator.h"

class PlayingState : public State {
	public:
		PlayingState(StateMachine& machine, GLWindow& glWindow, bool replace = true);

		void createMesh();
		void createShaders();

		void updateEvents();
		void update();
		void render();

	private:
		CubeGenerator cube;

		//Variables/Booleans
		GLuint screenWidth = SCREEN_WIDTH;
		GLuint screenHeight = SCREEN_HEIGHT;

		//Vectors
		std::vector<Mesh*> meshVector;
		std::vector<Shader*> shaderVector;
		std::vector<glm::vec3> cubePositionVector;

		//Arrays
		std::array<Texture, 2> texture;
		static const char* grassTexturePath; //Grass texture
		static const char* dirtTexturePath;  //Dirt texture

		//Camera info
		Camera camera;
		GLfloat lastX = screenWidth / 2.f;
		GLfloat lastY = screenHeight / 2.f;
		bool firstMouse = true;

		//Timing
		GLfloat deltaTime = 0.f;
		GLfloat lastFrame;

		//Shaders
		static const char* vShader; //Vertex shader
		static const char* fShader; //Fragment shader

		//Uniform variables
		GLuint uniformModel = 0, uniformProjection = 0, uniformView = 0;

		//Matrices
		glm::mat4 projection;
};

#endif