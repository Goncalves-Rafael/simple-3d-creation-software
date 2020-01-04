#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include "stb_image.h"

class Texture {
private:
  int width, height, nrChannels;
  unsigned char *data;
  unsigned int textureId;
public:
  Texture(char const *filename);
  unsigned int getId();
};

#endif
