#ifndef CHUNKGENERATOR_H
#define CHUNKGENERATOR_H

#include "State.h"
#include "CubeGenerator.h"
#include "GLWindow.h"
#include "HeightGenerator.h"
#include "Random.h"
#include "TreeGenerator.h"
#include "Frustum.h"

#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <algorithm>

class ChunkGenerator {
	public:
		ChunkGenerator() = default; 
		ChunkGenerator(glm::vec3 chunkPos, GLuint treeAmount);

		void update();
		void render(GLWindow& glWindow, glm::mat4 viewMatrix, glm::mat4 projection);

		void addBlock(CubeGenerator::BlockType blockType, const char* textureLocation, glm::vec3 position);
		void deleteBlock();

		GLuint getCubeAmount() const { return cubeVector.size(); }

		void createChunk();
		void createTrees();


	private:
		std::array<Random<>, 3> random;
		GLuint treeAmount;
		glm::vec3 chunkPos;

		std::unique_ptr<HeightGenerator> heightGenerator = nullptr; 
		std::vector<std::unique_ptr<CubeGenerator>> cubeVector;
		std::vector<std::unique_ptr<TreeGenerator>> treeVector;
};

#endif