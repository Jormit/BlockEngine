#include "collision.hpp"
using namespace std;

int isCollided(int chunk[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE], glm::vec3 position) {
    position.z = -(position.z - 1.0f);
    position.y = position.y - 1.0f;
    if (position.y < CHUNK_SIZE && position.z < CHUNK_SIZE && position.x < CHUNK_SIZE && position.y >= 0 && position.z >= 0 && position.x >= 0) {
        return chunk[(int)position.y][(int)position.x][(int)position.z] != -1;
    } else {
        return 0;
    }

}