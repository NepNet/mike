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

	//make a quad
	unsigned int vbo[2];
	unsigned int vao;

	glGenBuffers(2, vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	//vertex data
	float vertex_data[] = {
		//position			//normal	//uv
		-0.5f, -0.5f, 0,    0,0,0,      0,0,
		+0.5f, -0.5f, 0,    0,0,0,      0,0,
		+0.5f, +0.5f, 0,    0,0,0,      0,0,
		-0.5f, +0.5f, 0,    0,0,0,      0,0,
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
	unsigned int indices[] ={
		0,1,2,
		0,2,3
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);

	//init stuff
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	glCullFace(GL_BACK);

    // This is the render loop
    while (!glfwWindowShouldClose(window)) {
        ProcessInput(window);

#define CORNFLOWER_BLUE 0.039F, 0.58F, 0.93F

        glClearColor(CORNFLOWER_BLUE, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float time = (float)glfwGetTime();

    	glUseProgram(shader);
    	glBindVertexArray(vao);
    	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}