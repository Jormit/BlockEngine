#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define NONE  0
#define BELOW 1
#define ABOVE 2

#define PLAYER_X 0.9f
#define PLAYER_Y 2.0f
#define PLAYER_Z 0.9f

struct box {
    float minX;
    float maxX;
    float minY;
    float maxY;
    float minZ;
    float maxZ;
};

struct intLoc {
    int x;
    int y;
    int z;
};

int checkVerticalCollision(int chunk[16][16][16], glm::vec3 position);
void checkHorizontalCollision(int chunk[16][16][16], glm::vec3 position, int collisions[3][3]);
int checkBoxCollision(struct box box1,  struct box box2);
struct box getPlayerBox(glm::vec3 position);
int inBounds(int x, int y, int z);
struct box getStandardBlock(int x, int y, int z);