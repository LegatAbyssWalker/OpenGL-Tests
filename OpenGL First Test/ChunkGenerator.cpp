#include "ChunkGenerator.h"

ChunkGenerator::ChunkGenerator(GLint chunkXPos) {
	//Cube generation
	int vecNumber = 0;
	heightGenerator = std::make_unique<HeightGenerator>();

	/*-------------------------------------------------------------------------------------------------------------------*/
	//Creating blocks
	//Creates new blocks in a 16 by x by 16 area (including random height)
	for (GLsizei x = 0; x < CHUNK_SIZE; x++) {
		for (GLsizei z = 0; z < CHUNK_SIZE; z++) {
			for (GLsizei y = 0; y < CHUNK_SIZE; y++) {
				cubeVector.emplace_back(new CubeGenerator());

				if (y == CHUNK_SIZE - 1) { //15
					GLsizei heightY = heightGenerator->generateHeight(cubeVector[vecNumber - 1]->getPosition().x, cubeVector[vecNumber - 1]->getPosition().z);

					cubeVector[vecNumber]->setType(CubeGenerator::BlockType::Grass_Block);
					cubeVector[vecNumber]->setTexture(Texture::get(GRASS_TEXTURE_LOCATION));
					cubeVector[vecNumber]->setPosition(glm::vec3((GLint)x + (GLint)chunkXPos, (GLint)y + heightY, (GLint)z));
				}

				else if (y < CHUNK_SIZE - 1 && y > 5) { //6 - 15
					cubeVector[vecNumber]->setType(CubeGenerator::BlockType::Dirt_Block);
					cubeVector[vecNumber]->setTexture(Texture::get(DIRT_TEXTURE_LOCATION));
					cubeVector[vecNumber]->setPosition(glm::vec3((GLint)x + (GLint)chunkXPos, (GLint)y, (GLint)z));
				}

				else { //  0 - 5
					cubeVector[vecNumber]->setType(CubeGenerator::BlockType::Stone_Block);
					cubeVector[vecNumber]->setTexture(Texture::get(STONE_TEXTURE_LOCATION));
					cubeVector[vecNumber]->setPosition(glm::vec3((GLint)x + (GLint)chunkXPos, (GLint)y, (GLint)z));
				}

				vecNumber++;
			}
		}
	}

	//Sets dirt to places without dirt
	for (GLsizei x = 0; x < CHUNK_SIZE; x++) {
		for (GLsizei z = 0; z < CHUNK_SIZE; z++) {
			for (GLsizei y = CHUNK_SIZE - 1; y < CHUNK_SIZE * 2; y++) {
				if (y >= CHUNK_SIZE - 1 && y < CHUNK_SIZE * 2) {
					cubeVector.emplace_back(new CubeGenerator());

					cubeVector[vecNumber]->setType(CubeGenerator::BlockType::Dirt_Block);
					cubeVector[vecNumber]->setTexture(Texture::get(DIRT_TEXTURE_LOCATION));
					cubeVector[vecNumber]->setPosition(glm::vec3((GLint)x + (GLint)chunkXPos, (GLint)y, (GLint)z));
				}

				vecNumber++;
			}
		}
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	//Removing blocks
	//Places dirt blocks that are in same position as grass blocks, someplace else
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

void ChunkGenerator::update() {
	deleteBlock();


	//Removes blocks that (if ever placed) have the position less than 0
	for (auto& cube : cubeVector) {
		if (cube->getPosition().x < 0 || cube->getPosition().y < 0 || cube->getPosition().z < 0) {
			cube->setPosition(glm::vec3((GLint)BLOCK_DEATH_LOCATION));
		}
	}
}

void ChunkGenerator::render(GLWindow& glWindow, glm::mat4 viewMatrix) {
	for (auto& cube : cubeVector) {
		cube->render(glWindow, viewMatrix);
	}
}

void ChunkGenerator::addBlock(CubeGenerator::BlockType blockType, glm::vec3 position) {
	cubeVector.emplace_back(new CubeGenerator());

	switch (blockType) {
		case CubeGenerator::BlockType::Grass_Block:
			for (GLsizei a = cubeVector.size() - 1; a < cubeVector.size(); a++) {
				cubeVector[a]->setType(CubeGenerator::BlockType::Grass_Block);
				cubeVector[a]->setTexture(Texture::get(GRASS_TEXTURE_LOCATION));
				cubeVector[a]->setPosition(position);
			}
			break;

		case CubeGenerator::BlockType::Dirt_Block:
			for (GLsizei a = cubeVector.size() - 1; a < cubeVector.size(); a++) {
				cubeVector[a]->setType(CubeGenerator::BlockType::Dirt_Block);
				cubeVector[a]->setTexture(Texture::get(DIRT_TEXTURE_LOCATION));
				cubeVector[a]->setPosition(position);
			}
			break;

		case CubeGenerator::BlockType::Stone_Block:
			for (GLsizei a = cubeVector.size() - 1; a < cubeVector.size(); a++) {
				cubeVector[a]->setType(CubeGenerator::BlockType::Stone_Block);
				cubeVector[a]->setTexture(Texture::get(STONE_TEXTURE_LOCATION));
				cubeVector[a]->setPosition(position);
			}
			break;
	}
}

void ChunkGenerator::deleteBlock() {
	//Removing unused blocks
	auto cubeEnd = std::remove_if(cubeVector.begin(), cubeVector.end(), [](std::unique_ptr<CubeGenerator>& cube) {
		return cube->getPosition() == glm::vec3((GLint)BLOCK_DEATH_LOCATION);
	});
	cubeVector.erase(cubeEnd, cubeVector.end());
}
