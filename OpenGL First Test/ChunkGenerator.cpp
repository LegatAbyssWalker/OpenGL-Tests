#include "ChunkGenerator.h"

#include <iostream>

ChunkGenerator::ChunkGenerator(glm::vec3 chunkPos, GLuint treeAmount) : treeAmount(treeAmount), chunkPos(chunkPos) {

	// Cube generation
	createChunk();

	// Tree generation
	createTrees();
}

void ChunkGenerator::update() {
	deleteBlock();

	/*-------------------------------------------------------------------------------------------------------------------*/
	// Removes blocks if position.xyz < 0
	for (auto& cube : cubeVector) {
		cube->update();

		if (cube->getPosition().x < 0 || cube->getPosition().y < 0 || cube->getPosition().z < 0) {
			cube->setPosition(glm::vec3((GLint)BLOCK_DEATH_LOCATION));
		}
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	// Tree
	for (auto& tree : treeVector) {
		tree->update();
	}
}

void ChunkGenerator::render(GLWindow& glWindow, glm::mat4 viewMatrix, glm::mat4 projection) {
	Frustum frustum(projection * viewMatrix);

	for (auto& cube : cubeVector) {
		if (frustum.isAABBPartiallyInside(cube->getP0(), cube->getP1())) {
			cube->render(glWindow, viewMatrix, projection);
		}
	}


	for (auto& tree : treeVector) {
		tree->render(glWindow, viewMatrix, projection, frustum);
	}
}

void ChunkGenerator::addBlock(CubeGenerator::BlockType blockType, const char* textureLocation, glm::vec3 position) {
	cubeVector.emplace_back(new CubeGenerator());

	for (GLsizei a = cubeVector.size() - 1; a < cubeVector.size(); a++) {
		cubeVector[a]->setType(blockType);
		cubeVector[a]->setTexture(Texture::get(textureLocation));
		cubeVector[a]->setPosition(position);
	}
}

void ChunkGenerator::deleteBlock() {
	// Removing unused blocks
	auto cubeEnd = std::remove_if(cubeVector.begin(), cubeVector.end(), [](std::unique_ptr<CubeGenerator>& cube) {
		return cube->getPosition() == glm::vec3((GLint)BLOCK_DEATH_LOCATION);
	});
	cubeVector.erase(cubeEnd, cubeVector.end());
}

void ChunkGenerator::createChunk() {
	// Cube generation
	int vecNumber = 0;
	heightGenerator = std::make_unique<HeightGenerator>();

	/*-------------------------------------------------------------------------------------------------------------------*/
	// Creating blocks
	// Creates new blocks in a 16 by x by 16 area (x = random height)
	for (GLsizei x = 0; x < CHUNK_SIZE; x++) {
		for (GLsizei z = 0; z < CHUNK_SIZE; z++) {
			for (GLsizei y = 0; y < CHUNK_SIZE; y++) {
				cubeVector.emplace_back(new CubeGenerator());

				if (y == CHUNK_SIZE - 1) { // 15
					GLsizei heightY = heightGenerator->generateHeight(cubeVector[vecNumber - 1]->getPosition().x, cubeVector[vecNumber - 1]->getPosition().z);

					cubeVector[vecNumber]->setType(CubeGenerator::BlockType::Grass_Block);
					cubeVector[vecNumber]->setTexture(Texture::get(GRASS_TEXTURE_LOCATION));
					cubeVector[vecNumber]->setPosition(glm::vec3((GLint)x + (GLint)chunkPos.x, (GLint)y + heightY, (GLint)z + (GLint)chunkPos.z));
				}

				else if (y < CHUNK_SIZE - 1 && y > 5) { // 6 - 15
					cubeVector[vecNumber]->setType(CubeGenerator::BlockType::Dirt_Block);
					cubeVector[vecNumber]->setTexture(Texture::get(DIRT_TEXTURE_LOCATION));
					cubeVector[vecNumber]->setPosition(glm::vec3((GLint)x + (GLint)chunkPos.x, (GLint)y, (GLint)z + (GLint)chunkPos.z));
				}

				else { // 0 - 5
					cubeVector[vecNumber]->setType(CubeGenerator::BlockType::Stone_Block);
					cubeVector[vecNumber]->setTexture(Texture::get(STONE_TEXTURE_LOCATION));
					cubeVector[vecNumber]->setPosition(glm::vec3((GLint)x + (GLint)chunkPos.x, (GLint)y, (GLint)z + (GLint)chunkPos.z));
				}

				vecNumber++;
			}
		}
	}

	// Sets dirt to places without dirt
	for (GLsizei x = 0; x < CHUNK_SIZE; x++) {
		for (GLsizei z = 0; z < CHUNK_SIZE; z++) {
			for (GLsizei y = CHUNK_SIZE - 1; y < CHUNK_SIZE * 2; y++) {
				if (y >= CHUNK_SIZE - 1 && y < CHUNK_SIZE * 2) {
					cubeVector.emplace_back(new CubeGenerator());

					cubeVector[vecNumber]->setType(CubeGenerator::BlockType::Dirt_Block);
					cubeVector[vecNumber]->setTexture(Texture::get(DIRT_TEXTURE_LOCATION));
					cubeVector[vecNumber]->setPosition(glm::vec3((GLint)x + (GLint)chunkPos.x, (GLint)y, (GLint)z + (GLint)chunkPos.z));
				}

				vecNumber++;
			}
		}
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	// Removing blocks
	// Places dirt blocks that are in same position as grass blocks, someplace else
	for (GLsizei a = 0; a < cubeVector.size(); a++) {
		if (cubeVector[a]->getBlockType() == CubeGenerator::BlockType::Grass_Block) {
			for (GLsizei i = 0; i < cubeVector.size(); i++) {
				if ((cubeVector[i]->getBlockType() != CubeGenerator::BlockType::Grass_Block &&
					(cubeVector[i]->getPosition().x == cubeVector[a]->getPosition().x) &&
					(cubeVector[i]->getPosition().y >= cubeVector[a]->getPosition().y) &&
					(cubeVector[i]->getPosition().z == cubeVector[a]->getPosition().z))) {

					cubeVector[i]->setPosition(glm::vec3((GLint)BLOCK_DEATH_LOCATION));
				}
			}
		}
	}
}

void ChunkGenerator::createTrees() {
	GLint randomTreeAmount = random[2].getInt(0, treeAmount);

	for (GLsizei a = 0; a < randomTreeAmount; a++) {
		GLint posX = random[0].getInt(1, (CHUNK_SIZE + chunkPos.x) - 1);
		GLint posZ = random[1].getFloat(1, (CHUNK_SIZE + chunkPos.z) - 1); // New number when float
		GLint posY = 0;

		for (auto& cube : cubeVector) {
			if (cube->getBlockType() == CubeGenerator::BlockType::Grass_Block) {
				if (posX == cube->getPosition().x && posZ == cube->getPosition().z) {
					posY = (GLint)cube->getPosition().y + 1;
				}
			}
		}

		treeVector.emplace_back(new TreeGenerator(glm::vec3(posX, posY, posZ)));
	}
}
