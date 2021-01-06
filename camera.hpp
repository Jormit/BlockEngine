#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdlib.h>
#include <cmath>


// Class for managing camera state.
class Camera
{
public:
    Camera(glm::vec3 position, float yaw, float pitch, float speed, float sensitivity);
    glm::mat4 getViewMatrix();
    void processKeys(float deltaTime, GLFWwindow* window, int chunk[16][16][16]);
    void processMouse(float xoffset, float yoffset);
    glm::vec3 getPosition();

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 worldUp;

    void resolve_collision(glm::vec3 prevPos, glm::vec3 pointPos, int chunk[16][16][16]);

    float yaw;
    float pitch;

    float speed;
    float sensitivity;

    void update_vectors();

    int freeMode = 0;
    float velocityY = 0.0f;
    int isJump = 0;
    int onGround = 0;

    int fix_x, fix_y, fix_z;

};