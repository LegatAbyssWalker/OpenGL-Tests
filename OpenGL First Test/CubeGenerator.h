#ifndef CUBEGENERATOR_H
#define CUBEGENERATOR_H

#include "State.h"
#include "Mesh.h"
#include "Program.h"
#include "Texture.h"
#include "GLWindow.h"
#include "FileLocations.h"

#include <iostream>
#include <vector>

class CubeGenerator {
	public:
		enum BlockType {
			Grass_Block = 0,
			Dirt_Block = 1,
			Stone_Block = 2,
			Leaf_Block = 3,
			Log_Block = 4
		};

		CubeGenerator();

		void setType(CubeGenerator::BlockType blockType);
		void setTexture(std::shared_ptr<Texture> texture);
		void setPosition(glm::vec3 position = glm::vec3(0.f, 0.f, 0.f));

		void update();
		void render(GLWindow& glWindow, const glm::mat4 viewMatrix, const glm::mat4 projection);

		CubeGenerator::BlockType getBlockType() const { return blockType; }
		glm::vec3 getPosition() const { return glm::vec3(position); }
		
		glm::vec3 getP0() const { return getPosition() - glm::vec3(0.5f, 0.5f, 0.5f); }
		glm::vec3 getP1() const { return getPosition() + glm::vec3(0.5f, 0.5f, 0.5f); }

	private:
		CubeGenerator::BlockType blockType;

		Mesh mesh;
		std::shared_ptr<Program> program;
		std::shared_ptr<Texture> texture;

		glm::vec3 position;
		glm::vec3 scaleValue;

		std::vector<GLuint> vertices;
};

#endif