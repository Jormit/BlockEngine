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



int noise2(int x, int y);
float lin_inter(float x, float y, float s);
float smooth_inter(float x, float y, float s);
float noise2d(float x, float y);
float perlin2d(float x, float y, float freq, int depth);

class Map {
public:
    Map();
    void draw();
    int chunk[16][16][16];
private:
    unsigned int VAO, VBO, instanceVBO;

    void resetChunk();
    void placeBlocks(glm::vec3 translations[16][16][16], int chunk[16][16][16]);
    void generateChunk();
};
