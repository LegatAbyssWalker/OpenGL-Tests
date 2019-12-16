#ifndef CHUNKGENERATOR_H
#define CHUNKGENERATOR_H

#include "State.h"
#include "CubeGenerator.h"
#include "GLWindow.h"
#include "HeightGenerator.h"

#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <algorithm>

class ChunkGenerator {
	public:
		ChunkGenerator() = default; 
		ChunkGenerator(GLint chunkXPos);

		void update();
		void render(GLWindow& glWindow, glm::mat4 viewMatrix);

		void addBlock(CubeGenerator::BlockType blockType, glm::vec3 position);
		void deleteBlock();

		GLuint getCubeAmount() { return cubeVector.size(); }
		GLuint getChunkSize() { return CHUNK_SIZE; }
		
	private:
		const GLuint CHUNK_SIZE = 16;

		std::unique_ptr<HeightGenerator> heightGenerator = nullptr; 
		std::vector<std::unique_ptr<CubeGenerator>> cubeVector;
};

#endif