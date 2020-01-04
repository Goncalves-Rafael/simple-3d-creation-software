#include "texture.h"

Texture::Texture (char const *filename) {
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);
  // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  data = stbi_load(filename, &width, &height, &nrChannels, 0);
  if (data) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
  } else {
      std::cout << "Failed to load texture" << std::endl;
  }
  std::cout << sizeof(data) << std::endl;
  stbi_image_free(data);
}

unsigned int Texture::getId() {
  return textureId;
}
