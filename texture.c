//
// Created by nepnet on 10/1/25.
//

#include "texture.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "stb_image.h"

#include "glad/glad.h"

TextureHandle Texture_FromFile(char *path) {
	int width, height, nrChannels;
	unsigned char *data = stbi_load("resources/textures/grass.jpg", &width, &height, &nrChannels, 0);

	TextureHandle handle;
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	return handle;
}
