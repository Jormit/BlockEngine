#include "collision.hpp"
using namespace std;

// Check if the player is inside any of the 9 blocks underneath.
int checkVerticalCollision(int chunk[16][16][16], glm::vec3 position) {
    position.z = -(position.z - 1);
    struct box playerBox = getPlayerBox(position);
    struct intLoc playerInt;
    playerInt.x = (int)position.x;
    playerInt.y = (int)position.y;
    playerInt.z = (int)position.z;

    for (int x = -1; x <= 1; x++){
        for (int z = -1; z <= 1; z++){
            if (inBounds(playerInt.x + x, playerInt.y - 1, playerInt.z + z)) {
                if (chunk[playerInt.y - 1][playerInt.x + x][playerInt.z + z] != -1) {
                    struct box block = getStandardBlock(playerInt.x + x, playerInt.y - 1, playerInt.z + z);
                    if (checkBoxCollision(playerBox,  block)) {
                        return BELOW;
                    }
                }
            }
        }
    }
}

void checkHorizontalCollision(int chunk[16][16][16], glm::vec3 position, int collisions[3][3]) {
    position.z = -(position.z - 1);
    struct box playerBox = getPlayerBox(position);
    struct intLoc playerInt;
    playerInt.x = (int)position.x;
    playerInt.y = (int)position.y;
    playerInt.z = (int)position.z;

    //printf("x: %d y: %d z: %d\n", playerInt.x , playerInt.y, playerInt.z);

    for (int x = -1; x <= 1; x++){
        for (int z = -1; z <= 1; z++){
            if (inBounds(playerInt.x + x, playerInt.y - 1, playerInt.z + z)) {
                if (chunk[playerInt.y - 1][playerInt.x + x][playerInt.z + z] != -1) {
                    struct box block = getStandardBlock(playerInt.x + x, playerInt.y - 1, playerInt.z + z);
                    if (checkBoxCollision(playerBox,  block)) {
                        collisions[x + 1][z + 1] = 1;
                        continue;
                    }
                }
            }
            collisions[x + 1][z + 1] = 0;
        }
    }
}

int checkBoxCollision(struct box box1,  struct box box2) {
    return
    (box1.minX <= box2.maxX && box1.maxX >= box2.minX) &&
    (box1.minY <= box2.maxY && box1.maxY >= box2.minY) &&
    (box1.minZ <= box2.maxZ && box1.maxZ >= box2.minZ);
}

struct box getPlayerBox(glm::vec3 position) {
    struct box playerBox;
    playerBox.minX = position.x - (PLAYER_X / 2.0f);
    playerBox.maxX = position.x + (PLAYER_X / 2.0f);
    playerBox.minY = position.y - (PLAYER_Y / 2.0f);
    playerBox.maxY = position.y + (PLAYER_Y / 2.0f);
    playerBox.minZ = position.z - (PLAYER_Z / 2.0f);
    playerBox.maxZ = position.z + (PLAYER_Z / 2.0f);
    return playerBox;
}

struct box getStandardBlock(int x, int y, int z){
    struct box block;
    block.minX = (float) (x);
    block.maxX = (float) (x) + 1.0f;
    block.minZ = (float) (z);
    block.maxZ = (float) (z) + 1.0f;
    block.minY = (float) (y);
    block.maxY = (float) (y) + 1.0f;
    return block;
}

int inBounds(int x, int y, int z) {
    return (x < 16 && x >= 0) && (y < 16 && y >= 0) && (z < 16 && z >= 0);
}

int isCollided(int chunk[16][16][16], glm::vec3 position) {
    position.z = -(position.z - 1);
    position.y = position.y - 1;
    if (position.y < 16 && position.z < 16 && position.x < 16 && position.y >= 0 && position.z >= 0 && position.x >= 0) {
        return chunk[(int)position.y][(int)position.x][(int)position.z] != -1;
    } else {
        return 0;
    }

}