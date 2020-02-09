#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>

#include "cubeVertices.hpp"

#define CHUNK_SIZE (16 * 16 * 16)
#define TEXTURE_BLOCK_SIZE (0.0625f)
#define NONE (-1)

int noise2(int x, int y);
float lin_inter(float x, float y, float s);
float smooth_inter(float x, float y, float s);
float noise2d(float x, float y);
float perlin2d(float x, float y, float freq, int depth);

struct vertex {
    glm::vec3 vertex;
    glm::vec3 normal;
    glm::vec2 texture;
};

struct cube {
    struct vertex vertices[36];
};

class Map {
public:
    Map();
    void draw();
    int chunk[16][16][16];
    std::vector<cube> cubes;
private:
    unsigned int VAO, VBO, instanceVBO, textureVBO;

    void resetChunk();
    struct cube generateCube(glm::vec3 translation, int texture);
    void placeBlocks(int chunk[16][16][16]);
    void generateChunk();
};
