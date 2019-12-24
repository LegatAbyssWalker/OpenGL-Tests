#ifndef WORLD_H
#define WORLD_H

#include "State.h"
#include "GLWindow.h"
#include "Mesh.h"
#include "MoreInfo.h"
#include "FileLocations.h"
#include "Texture.h"
#include "ChunkGenerator.h"
#include "TreeGenerator.h"
#include "GLWindow.h"

#include <iostream>
#include <vector>
#include <memory>

class World {
	public:
		World(GLWindow& glWindow);
	
		void update();
		void render(glm::mat4 viewMatrix);

		glm::mat4 getProjectionMatrix();
		
	private:
		GLWindow glWindow;

		std::vector<std::unique_ptr<ChunkGenerator>> chunkVector;
		glm::mat4 projectionMatrix;
};

#endif