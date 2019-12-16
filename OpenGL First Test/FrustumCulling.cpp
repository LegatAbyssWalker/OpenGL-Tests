#include "FrustumCulling.h"

FrustumCulling::FrustumCulling() {
}

void FrustumCulling::setFrustum(GLfloat angle, GLfloat ratio, GLfloat, GLfloat) {
}

void FrustumCulling::setCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up) {
}

int FrustumCulling::cubeInFrustum(const glm::vec3& center, GLfloat x, GLfloat y, GLfloat z) {
	int result = FRUSTUM_INSIDE;
/*
	for (size_t x = 0; x < 6; x++) {
		int out = 0;
		int in = 0;

		if (planes[x].getPointDistance(center + glm::vec3(-x, -y, -z)) < 0) { out++; }
		else { in++; }

		if (planes[x].getPointDistance(center + glm::vec3(x, -y, -z)) < 0) { out++; }
		else { in++; }

		if (planes[x].getPointDistance(center + glm::vec3(-x, -y, z)) < 0) { out++; }
		else { in++; }

		if (planes[x].getPointDistance(center + glm::vec3(x, -y, z)) < 0) { out++; }
		else { in++; }

		if (planes[x].getPointDistance(center + glm::vec3(-x, y, -z)) < 0) { out++; }
		else { in++; }

		if (planes[x].getPointDistance(center + glm::vec3(x, y, -z)) < 0) { out++; }
		else { in++; }

		if (planes[x].getPointDistance(center + glm::vec3(-x, y, z)) < 0) { out++; }
		else { in++; }

		if (planes[x].getPointDistance(center + glm::vec3(x, y, z)) < 0) { out++; }
		else { in++; }

		// If all corners are out
		if (!in) {
			return FRUSTUM_OUTSIDE;
		}
		// If some corners are out and others are in	
		else if (out) {
			result = FRUSTUM_INTERSECT;
		}
	}
	*/
	return(result);
}
