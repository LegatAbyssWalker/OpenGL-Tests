#include "World.h"

World::World() {
	//Chunk generation
	GLsizei chunkXPos = 0;

	for (GLsizei x = 0; x < 1; x++) {
		chunkVector.emplace_back(new ChunkGenerator(chunkXPos));
		chunkXPos += chunkVector[x]->getChunkSize();
	}
}

void World::update() {
	for (auto& chunk : chunkVector) {
		chunk->update();
	}
}

void World::render(GLWindow& glWindow, glm::mat4 viewMatrix) {
	for (auto& chunk : chunkVector) {
		chunk->render(glWindow, viewMatrix);
	}
}
