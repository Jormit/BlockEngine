#include "camera.hpp"
#include "collision.hpp"

using namespace std;

Camera::Camera(glm::vec3 position, float yaw, float pitch, float speed, float sensitivity) {
    this->position = position;
    this->yaw = yaw;
    this->pitch = pitch;
    this->speed = speed;
    this->sensitivity = sensitivity;
    this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    float lastDy = 0.0f;
    update_vectors();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

void Camera::update_vectors() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up    = glm::normalize(glm::cross(right, front));
}

void Camera::processKeys(float deltaTime, GLFWwindow* window, int chunk[16][16][16]) {
    // Move the camera.
    float velocity = deltaTime * speed;
    glm::vec3 prevPos = position;

    if (freeMode) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            position += front * velocity;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            position -= front * velocity;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            position -= right * velocity;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            position += right * velocity;
    } else {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            position.x += front.x * velocity;
            position.z += front.z * velocity;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            position.x -= front.x * velocity;
            position.z -= front.z * velocity;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            position -= right * velocity;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            position += right * velocity;

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            if (!isJump){
                velocityY = 7.0f;
                isJump = 1;
            }
        }

        float gravity = -9.8f;
        velocityY += deltaTime * gravity;
        position.y += deltaTime * velocityY;
    }

    if (checkVerticalCollision(chunk, position) == BELOW) {
        position.y = prevPos.y;
        velocityY = 0.0f;
        isJump = 0;
    }

    int collisions[3][3];
    checkHorizontalCollision(chunk, position, collisions);

    if (collisions[0][1] || collisions[2][1]) {
        position.x = prevPos.x;
    } if (collisions[1][2] || collisions[1][0]) {
        position.z = prevPos.z;
    }
    //printf("x: %f y: %f z: %f\n", position.x, position.y, position.z - 1);
    /*printf("%d %d %d\n%d %d %d\n%d %d %d\n=====\n",
            collisions[0][2], collisions[1][2], collisions[2][2],
            collisions[0][1], collisions[1][1], collisions[2][1],
            collisions[0][0], collisions[1][0], collisions[2][0]);*/
}

void Camera::processMouse(float xoffset, float yoffset) {
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    update_vectors();

}

glm::vec3 Camera::getPosition(){
    return position;
}

