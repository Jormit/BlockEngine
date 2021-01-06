#include "collision.hpp"
using namespace std;

int isCollided(int chunk[16][16][16], glm::vec3 position) {
    position.z = -(position.z - 1.0f);
    position.y = position.y - 1.0f;
    if (position.y < 16 && position.z < 16 && position.x < 16 && position.y >= 0 && position.z >= 0 && position.x >= 0) {
        return chunk[(int)position.y][(int)position.x][(int)position.z] != -1;
    } else {
        return 0;
    }

}