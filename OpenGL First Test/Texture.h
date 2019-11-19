#ifndef TEXTURE_H
#define TEXTURE_H

#include "GL/glew.h"
#include "stb_image.h"

#include <iostream>

class Texture {
	public:
		Texture() = default;
		Texture(const char* fileLocation);
		~Texture();

		void loadTexture();
		void useTexture();
		void clearTexture();


	private:
		GLuint textureID;
		int width, height, bitDepth;

		const char* fileLocation;
};

#endif