#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNorm;
layout (location = 2) in vec2 inTex;
layout (location = 3) in vec3 aOffset;
layout (location = 4) in vec3 display;

uniform mat4 view;
uniform mat4 projection;

out vec2 texCoord;

void main() {
    gl_Position =  projection * view * vec4(inPos + aOffset, 1.0);
    texCoord = inTex;
}