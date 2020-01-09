#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 projection = mat4(1.0f);

out vec4 vertexColor;
out vec2 texCoord;

void main(){
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   // gl_Position = vec4(aPos, 1.0);
   vertexColor = vec4(aPos, 1.0);
   texCoord = aTexCoord;
}
