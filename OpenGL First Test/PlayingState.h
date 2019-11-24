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
#include "Program.h"
#include "Camera.h"
#include "MoreInfo.h"
#include "Texture.h"
#include "CubeGenerator.h"

class PlayingState : public State {
	public:
		PlayingState(StateMachine& machine, GLWindow& glWindow, bool replace = true);

		void updateEvents();
		void update();
		void render();

	private:
		//Vectors
		std::vector<CubeGenerator> cubeVector;

		//Variables/Booleans
		GLuint screenWidth = SCREEN_WIDTH;
		GLuint screenHeight = SCREEN_HEIGHT;

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
};

#endif