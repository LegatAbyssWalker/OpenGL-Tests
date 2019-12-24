#ifndef TREEGENERATOR_H
#define TREEGENERATOR_H

#include "State.h"
#include "CubeGenerator.h"
#include "GLWindow.h"
#include "HeightGenerator.h"
#include "Random.h"
#include "Frustum.h"

#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <algorithm>

class TreeGenerator {
	public:
		TreeGenerator() = default;
		TreeGenerator(glm::vec3 position);

		void update();
		void render(GLWindow& glWindow, glm::mat4 viewMatrix, glm::mat4 projection, const Frustum& frustum);
		

	private:
		std::vector<std::unique_ptr<CubeGenerator>> cubeVector;
};

#endif