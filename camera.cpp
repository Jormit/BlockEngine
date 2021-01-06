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

void Camera::processKeys(float deltaTime, GLFWwindow* window, int chunk[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]) {
    // Move the camera.
    float velocity = deltaTime * speed;
    glm::vec3 prevPos = position;

    fix_x = 0;
    fix_y = 0;
    fix_z = 0;

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
            if (onGround){
                velocityY = 7.0f;
                onGround = 0;
            }
        }
    }

    if (!onGround) {
        float gravity = -9.8f;
        velocityY += deltaTime * gravity;
        position.y += deltaTime * velocityY;
    } else {
        velocityY = -1.0f;
        position.y += deltaTime * velocityY;
    }

    onGround = 0;

    resolve_collision(glm::vec3(prevPos.x - 0.3f, prevPos.y, prevPos.z - 0.3f),
            glm::vec3(position.x - 0.3f, position.y, position.z - 0.3f), chunk);
    resolve_collision(glm::vec3(prevPos.x + 0.3f, prevPos.y, prevPos.z - 0.3f),
            glm::vec3(position.x + 0.3f, position.y, position.z - 0.3f), chunk);
    resolve_collision(glm::vec3(prevPos.x - 0.3f, prevPos.y, prevPos.z + 0.3f),
            glm::vec3(position.x - 0.3f, position.y, position.z + 0.3f), chunk);
    resolve_collision(glm::vec3(prevPos.x + 0.3f, prevPos.y, prevPos.z + 0.3f),
            glm::vec3(position.x + 0.3f, position.y, position.z + 0.3f), chunk);

    if (fix_x) {
        position.x = prevPos.x;
    } if (fix_y) {
        position.y = prevPos.y;
    } if (fix_z) {
        position.z = prevPos.z;
    }
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

glm::vec3 Camera::getFront() {
    return front;
}

void Camera::resolve_collision(glm::vec3 prevPos, glm::vec3 pointPos, int chunk[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]) {
    // Check if is collided.
    if (isCollided(chunk, pointPos)) {
        // Restrict axis causing collision.

        if (!isCollided(chunk, glm::vec3(pointPos.x, prevPos.y, pointPos.z))) {
            fix_y = 1;
            onGround = 1;
        } else if (!isCollided(chunk, glm::vec3(prevPos.x, pointPos.y, pointPos.z))) {
            fix_x = 1;
        } else if (!isCollided(chunk, glm::vec3(pointPos.x, pointPos.y, prevPos.z))) {
            fix_z = 1;
        } else if (!isCollided(chunk, glm::vec3(prevPos.x, pointPos.y, prevPos.z))) {
            fix_x = 1;
            fix_z = 1;

        } else if (!isCollided(chunk, glm::vec3(prevPos.x, prevPos.y, pointPos.z))) {
            fix_x = 1;
            fix_y = 1;
            onGround = 1;
        } else if (!isCollided(chunk, glm::vec3(pointPos.x, prevPos.y, prevPos.z))) {
            fix_z = 1;
            fix_y = 1;
            onGround = 1;
        } else if (!isCollided(chunk, glm::vec3(prevPos.x, prevPos.y, prevPos.z))) {
            fix_x = 1;
            fix_z = 1;
            fix_y = 1;
            onGround = 1;
        } else {
            fix_x = 1;
            fix_z = 1;
            fix_y = 1;
        }
    }
}

