#include "World.h"

World::World(GLWindow& glWindow) : glWindow(glWindow) {
	// Chunk generation
	GLsizei TOTAL_CHUNK_AMOUNT = 2; // MULTIPLE OF 2
	GLsizei TOTAL_TREE_AMOUNT_PER_CHUNK = 5;

	for (GLsizei x = 0; x < TOTAL_CHUNK_AMOUNT / 2; x++) {
		for (GLsizei z = 0; z < TOTAL_CHUNK_AMOUNT / 2; z++) {
			chunkVector.emplace_back(new ChunkGenerator(glm::vec3(x * CHUNK_SIZE, NULL, z * CHUNK_SIZE), TOTAL_TREE_AMOUNT_PER_CHUNK));
		}
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
}

void World::update() {
	for (auto& chunk : chunkVector) {
		chunk->update();
	}
}

void World::render(glm::mat4 viewMatrix) {
	// Projection
	glm::mat4 projection = glm::perspective(glm::radians(45.f), (GLfloat)glWindow.getBufferWidth() / glWindow.getBufferHeight(), 0.1f, 100.f);;

	for (auto& chunk : chunkVector) {
		chunk->render(glWindow, viewMatrix, projection);
	}
}

glm::mat4 World::getProjectionMatrix() {
	return glm::perspective(glm::radians(45.f), (GLfloat)glWindow.getBufferWidth() / glWindow.getBufferHeight(), 0.1f, 100.f);
}
