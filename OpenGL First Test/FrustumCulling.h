#ifndef FRUSTUMCULLING
#define FRUSTUMCULLING

#include "State.h"

#include <iostream>

class FrustumCulling {
	public:
		FrustumCulling();

		void setFrustum(GLfloat angle, GLfloat ratio, GLfloat near, GLfloat far);
		void setCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);

		int cubeInFrustum(const glm::vec3& center, GLfloat x, GLfloat y, GLfloat z);

		enum {
			FRUSTUM_TOP = 0,
			FRUSTUM_BOTTOM,
			FRUSTUM_LEFT,
			FRUSTUM_RIGHT,
			FRUSTUM_NEAR,
			FRUSTUM_FAR
		};

		static enum {
			FRUSTUM_OUTSIDE = 0,
			FRUSTUM_INTERSECT,
			FRUSTUM_INSIDE
		};


	private:
	//	Plane3D planes[6];

		glm::vec3 nearTopLeft, nearTopRight, nearBottomLeft, nearBottomRight;
		glm::vec3 farTopLeft, farTopRight, farBottomLeft, farBottomRight;

		GLfloat nearDistance, farDistance;
		GLfloat nearWidth, nearHeight;
		GLfloat farWidth, farHeight;
		GLfloat ratio, angle, tang;
};

#endif