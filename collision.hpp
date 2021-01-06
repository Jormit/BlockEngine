#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "config.hpp"

int isCollided(int chunk[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE], glm::vec3 position);