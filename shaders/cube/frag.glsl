#version 330 core
in vec2 texCoord;
uniform sampler2D blockTexture;
out vec4 FragColor;

void main(){
    FragColor = texture(blockTexture, texCoord);
}
