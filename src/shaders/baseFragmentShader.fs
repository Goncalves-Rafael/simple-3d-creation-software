#version 330 core

in vec4 vertexColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform vec4 color;
uniform int colorSet = 0;

void main() {
  // FragColor = texture(ourTexture, texCoord) * vertexColor;
  if(colorSet == 1) {
    FragColor = color;
  } else {
    FragColor = vertexColor;
  }
}
