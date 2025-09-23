#include <stdio.h>
#include <stdbool.h>

#define ARENA_IMPLEMENTATION
#include "arena.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "shader.h"

Arena meow;

#define NORMALIZE_RGB(r, g, b) ((r) / 255.0f), ((g) / 255.0f), ((b) / 255.0f)

void ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void OnResize(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main(void) {
	//Meow
	arena_alloc(&meow, 1024*1024);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    // Construct the window
    GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "Mike", monitor, NULL);
    if (!window) {
        printf("Failed to create the GLFW window\n");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    // Handle view port dimensions
    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, OnResize);

    //mat4 look;
    //glm_lookat(camera.transform.position, (float[3]){0,0,0},(float[3]){0,1,0}, look );

	//load shader
	Shader shader = shader_load_from_file("resources/shaders/test.vert", "resources/shaders/test.frag");

	//

    // This is the render loop
    while (!glfwWindowShouldClose(window)) {
        ProcessInput(window);

#define CORNFLOWER_BLUE 0.039F, 0.58F, 0.93F

        glClearColor(CORNFLOWER_BLUE, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float time = (float)glfwGetTime();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}