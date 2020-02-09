#include "map.hpp"
using namespace std;

static int SEED = 1;
static int mHash[] = {208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
                     185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
                     9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
                     70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
                     203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
                     164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
                     228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
                     232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
                     193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
                     101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
                     135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
                     114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219};

float texture_uneven[] = {0.0000f, 0.0625f, 0.0625f, 0.0625f, 0.0625f, 0.1250f, 0.0000f,
                          0.0625f, 0.0000f, 0.1250f, 0.0625f, 0.1250f, 0.0000f, 0.0625f,
                          0.0625f, 0.0625f, 0.0625f, 0.1250f, 0.0000f, 0.0625f, 0.0000f,
                          0.1250f, 0.0625f, 0.1250f, 0.0000f, 0.0000f, 0.0000f, 0.0625f,
                          0.0625f, 0.0625f, 0.0000f, 0.0000f, 0.0625f, 0.0625f, 0.0625f,
                          0.0000f, 0.0000f, 0.1250f, 0.0000f, 0.1875f, 0.0625f, 0.1875f,
                          0.0000f, 0.1250f, 0.0625f, 0.1875f, 0.0625f, 0.1250f, 0.0000f,
                          0.0625f, 0.0000f, 0.1250f, 0.0625f, 0.1250f, 0.0000f, 0.0625f,
                          0.0625f, 0.0625f, 0.0625f, 0.1250f, 0.0000f, 0.0625f, 0.0000f,
                          0.1250f, 0.0625f, 0.1250f, 0.0000f, 0.0625f, 0.0625f, 0.0625f,
                          0.0625f, 0.1250f};

float texture_even[] = {  0.0000f, 0.0000f, 0.0625f, 0.0000f, 0.0625f, 0.0625f, 0.0000f,
                          0.0000f, 0.0000f, 0.0625f, 0.0625f, 0.0625f, 0.0000f, 0.0000f,
                          0.0625f, 0.0000f, 0.0625f, 0.0625f, 0.0000f, 0.0000f, 0.0000f,
                          0.0625f, 0.0625f, 0.0625f, 0.0000f, 0.0000f, 0.0000f, 0.0625f,
                          0.0625f, 0.0625f, 0.0000f, 0.0000f, 0.0625f, 0.0625f, 0.0625f,
                          0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0625f, 0.0625f, 0.0625f,
                          0.0000f, 0.0000f, 0.0625f, 0.0625f, 0.0625f, 0.0000f, 0.0000f,
                          0.0000f, 0.0000f, 0.0625f, 0.0625f, 0.0625f, 0.0000f, 0.0000f,
                          0.0625f, 0.0000f, 0.0625f, 0.0625f, 0.0000f, 0.0000f, 0.0000f,
                          0.0625f, 0.0625f, 0.0625f, 0.0000f, 0.0000f, 0.0625f, 0.0000f,
                          0.0625f, 0.0625f};

int is_uneven[16] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0};

float std_cube[] = {
        // FRONT FACE.     // Normals.
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f,-1.0f,
        1.0f, 0.0f, 0.0f,  0.0f, 0.0f,-1.0f,
        1.0f, 1.0f, 0.0f,  0.0f, 0.0f,-1.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f,-1.0f,
        0.0f, 1.0f, 0.0f,  0.0f, 0.0f,-1.0f,
        1.0f, 1.0f, 0.0f,  0.0f, 0.0f,-1.0f,

        // BACK FACE.
        0.0f, 0.0f,1.0f,  0.0f, 0.0f, 1.0f,
        1.0f, 0.0f,1.0f,  0.0f, 0.0f, 1.0f,
        1.0f, 1.0f,1.0f,  0.0f, 0.0f, 1.0f,
        0.0f, 0.0f,1.0f,  0.0f, 0.0f, 1.0f,
        0.0f, 1.0f,1.0f,  0.0f, 0.0f, 1.0f,
        1.0f, 1.0f,1.0f,  0.0f, 0.0f, 1.0f,

        // BOTTOM FACE.
        0.0f, 0.0f, 0.0f,  0.0f,-1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,  0.0f,-1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,  0.0f,-1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,  0.0f,-1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,  0.0f,-1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,  0.0f,-1.0f, 0.0f,

        // TOP FACE.
        0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,

        // LEFT FACE.
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,

        // RIGHT FACE.
        1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f
};

Map::Map() {
    generateChunk();
    chunk[15][15][15] = 5;
    placeBlocks(chunk);


    // Generate VBO, VAO for Quad.
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, cubes.size() * 36 * sizeof(vertex), &cubes[0], GL_STATIC_DRAW);

    // Setup Position, Normal and Texture attributes for Quad.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Map::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, cubes.size() * 36 * sizeof(vertex));
}

void Map::resetChunk() {
    for (int y = 0; y < 16; y++){
        for (int x = 0; x < 16; x++){
            for (int z = 0; z < 16; z++){
                chunk[y][x][z] = -1;
            }
        }
    }
}

void Map::placeBlocks(int chunk[16][16][16]) {
    for (int y = 0; y < 16; y++){
        for (int x = 0; x < 16; x++){
            for (int z = 0; z < 16; z++){
                if (chunk[y][x][z] != NONE) {
                    cubes.push_back(generateCube(glm::vec3((float)x, (float)y, -(float)z), chunk[y][x][z]));
                }
            }
        }
    }
}

struct cube Map::generateCube(glm::vec3 translation, int texture) {
    struct cube newCube{};
    for (int i = 0; i < 36; i++) {
        int vertexIndex = i * 6;
        newCube.vertices[i].vertex = glm::vec3 (std_cube[vertexIndex], std_cube[vertexIndex + 1], std_cube[vertexIndex + 2]) + translation;
        newCube.vertices[i].normal = glm::vec3 (std_cube[vertexIndex + 3], std_cube[vertexIndex + 4], std_cube[vertexIndex + 5]);

        vertexIndex = i * 2;
        if (is_uneven[texture]) {
            newCube.vertices[i].texture = glm::vec2 (texture_uneven[vertexIndex] + TEXTURE_BLOCK_SIZE * texture, texture_uneven[vertexIndex + 1]);
        } else {
            newCube.vertices[i].texture = glm::vec2 (texture_even[vertexIndex] + TEXTURE_BLOCK_SIZE * texture, texture_even[vertexIndex + 1]);
        }
    }
    return newCube;
}

void Map::generateChunk() {
    resetChunk();

    // Generate a height map.
    float heightMap[16][16];
    for (int x = 0; x < 16; x++){
        for (int z = 0; z < 16; z++){
            heightMap[x][z] = perlin2d((float)x, (float)z, 0.1, 4);
        }
    }
    // Apply to chunk.
    for (int y = 0; y < 16; y++){
        for (int x = 0; x < 16; x++){
            for (int z = 0; z < 16; z++){
                if (((float)(y)/(float)(16)) < heightMap[x][z]){
                    chunk[y][x][z] = 0;
                }
            }
        }
    }
}

// Noise generation ALGORITHMS (Taken from github).
// https://gist.github.com/nowl/828013.
// ===================================================
int noise2(int x, int y)
{
    int tmp = mHash[(y + SEED) % 256];
    return mHash[(tmp + x) % 256];
}

float lin_inter(float x, float y, float s)
{
    return x + s * (y-x);
}

float smooth_inter(float x, float y, float s)
{
    return lin_inter(x, y, s * s * (3-2*s));
}

float noise2d(float x, float y)
{
    int x_int = x;
    int y_int = y;
    float x_frac = x - x_int;
    float y_frac = y - y_int;
    int s = noise2(x_int, y_int);
    int t = noise2(x_int+1, y_int);
    int u = noise2(x_int, y_int+1);
    int v = noise2(x_int+1, y_int+1);
    float low = smooth_inter(s, t, x_frac);
    float high = smooth_inter(u, v, x_frac);
    return smooth_inter(low, high, y_frac);
}

float perlin2d(float x, float y, float freq, int depth)
{
    float xa = x*freq;
    float ya = y*freq;
    float amp = 1.0;
    float fin = 0;
    float div = 0.0;

    int i;
    for(i=0; i<depth; i++)
    {
        div += 256 * amp;
        fin += noise2d(xa, ya) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }

    return fin/div;
}


