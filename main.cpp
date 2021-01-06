#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera.hpp"
#include "shader.hpp"
#include "map.hpp"
#include "texture.hpp"
#include "config.hpp"

using namespace std;

#define WIDTH 980
#define HEIGHT 620

// Function Declarations.
void processInput(GLFWwindow *window, float deltaTime);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback (GLFWwindow* window, double xpos, double ypos);
GLFWwindow* initGL();

// Camera setup.
Camera camera(glm::vec3(7.0f, CHUNK_SIZE + 1.0f, -7.0f), -90.0f, 0.0f, 5.0f, 0.1f);
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime;
float lastFrame;

int main() {
    // Initialize opengl;
    GLFWwindow *window = initGL();
    if (window == NULL) {
        cerr << "Could not initialize an OpenGL Context" << endl;
    }
    Map map1;
    Shader cubeShader("../shaders/cube/vert.glsl", "../shaders/cube/frag.glsl");
    Texture text1("../assets/textures/texture.bmp");

    while (!glfwWindowShouldClose(window)) {
        // Calculate delta time.
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Clear screen and z-buffer.
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput(window, deltaTime);
        camera.processKeys(deltaTime, window, map1.chunk);

        // Send matrices to the shader.
        cubeShader.setMat4("view", camera.getViewMatrix());
        cubeShader.setMat4("projection", glm::perspective(glm::radians(45.0f), (float) WIDTH / (float) HEIGHT, 0.1f, 100.0f));

        text1.bindTexture();
        cubeShader.use();

        // Draw geometry.
        map1.draw();
        map1.focus(camera.getPosition(), camera.getFront());

        // Flip the buffers and check for events.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}

void processInput(GLFWwindow *window, float deltaTime){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback (GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.processMouse(xoffset, yoffset);
}

GLFWwindow* initGL() {
    GLFWwindow *window = NULL;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "BlockEngine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return window;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return window;
    }

    glEnable(GL_DEPTH_TEST);
    return window;
}