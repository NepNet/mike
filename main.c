#include <stdio.h>
#include <stdbool.h>

#define ARENA_IMPLEMENTATION
#include <string.h>

#include "arena.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "shader.h"

#include "player.h"
#include "chunk.h"

Arena meow;

#define NORMALIZE_RGB(r, g, b) ((r) / 255.0f), ((g) / 255.0f), ((b) / 255.0f)

float aspect = 1;

struct cameraData {
	mat4 projection, view;
} cam_data;

float nearPlane = 0.01f;
float farPlane = 100.0f;
float fov = 60 * 0.0174533f;

float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float lastX = 400, lastY = 300;

void ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	PlayerData *player_data = player_get_player_data();

	float moveSpeed = 2.5f;

	vec3 front = {cos(player_data->yaw * 0.0174533f), 0, sin(player_data->yaw * 0.0174533f)};
	vec3 right;
	glm_cross(front, (vec3){0.0f, 1.0f, 0.0f}, right);

	vec3 speed = {moveSpeed * deltaTime, moveSpeed * deltaTime, moveSpeed * deltaTime};

	glm_vec3_mul(front, speed, front);
	glm_vec3_mul(right, speed, right);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		glm_vec3_sub(player_data->position, right, player_data->position);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		glm_vec3_add(player_data->position, right, player_data->position);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		glm_vec3_add(player_data->position, front, player_data->position);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		glm_vec3_sub(player_data->position, front, player_data->position);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		player_data->position[1] += moveSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		player_data->position[1] -= moveSpeed * deltaTime;
	}
}

void OnResize(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
	aspect = (float) width / (float) height;
}

bool firstMouse = true;

void OnMouseMove(GLFWwindow *window, double xPos, double yPos) {
	if (firstMouse) // initially set to true
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos; // reversed since y-coordinates range from bottom to top
	lastX = xPos;
	lastY = yPos;

	const float sensitivity = 0.1f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	PlayerData *player_data = player_get_player_data();

	player_data->yaw += xOffset;
	player_data->pitch += yOffset;
}

Chunk *chunk;

int main(void) {
	//Meow
	arena_alloc(&meow, 1024 * 1024);

	chunk = malloc(sizeof(Chunk));
	Chunk_FillWave(chunk);

	glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *mode = glfwGetVideoMode(monitor);

	// Construct the window
	//  GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "Mike", monitor, NULL);
	GLFWwindow *window = glfwCreateWindow(800, 600, "Mike", NULL, NULL);
	aspect = (float) mode->width / (float) mode->height;
	aspect = (float) 800 / (float) 600;
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, OnMouseMove);

	//load shader
	Shader shader = shader_load_from_file("resources/shaders/test.vert", "resources/shaders/test.frag");

	//make a quad
	unsigned int vbo[2];
	unsigned int vao;

	glGenBuffers(2, vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	#include "cube.h"
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);
	glBindVertexArray(0);

	//init stuff
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	glCullFace(GL_BACK);

	int localToWorldLoc = glGetUniformLocation(shader, "localToWorld");

	unsigned int cameraBlockIndex = glGetUniformBlockIndex(shader, "Camera");
	glUniformBlockBinding(shader, cameraBlockIndex, 0);
	unsigned int cameraDataBuffer;
	glGenBuffers(1, &cameraDataBuffer);

	memcpy(cam_data.view, GLM_MAT4_IDENTITY, sizeof(mat4));
	memcpy(cam_data.projection, GLM_MAT4_IDENTITY, sizeof(mat4));


	glm_perspective(fov, aspect, nearPlane, farPlane, cam_data.projection);

	glBindBuffer(GL_UNIFORM_BUFFER, cameraDataBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(cam_data), &cam_data, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, cameraDataBuffer);

	player_get_player_data()->position[2] = 2;
	player_get_player_data()->yaw = -90.0f;

	// This is the render loop
	while (!glfwWindowShouldClose(window)) {
		float time = (float) glfwGetTime();
		deltaTime = time - lastFrame;
		lastFrame = time;

		ProcessInput(window);

		#define CORNFLOWER_BLUE 0.039F, 0.58F, 0.93F

		glClearColor(CORNFLOWER_BLUE, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		player_get_view(cam_data.view);

		glm_perspective(fov, aspect, nearPlane, farPlane, cam_data.projection);

		glBindBuffer(GL_UNIFORM_BUFFER, cameraDataBuffer);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(cam_data), &cam_data, GL_STATIC_DRAW);

		glUseProgram(shader);
		glBindVertexArray(vao);
		for (int i = 0; i < 5; i++) {
			vec4 *model = GLM_MAT4_IDENTITY;
			glm_translate(model, (vec3){i * 2 - 5, 0.0f, 0});
			glUniformMatrix4fv(localToWorldLoc, 1, GL_FALSE, (float *) model);

			glDrawElements(GL_TRIANGLES, cube_indices_count, GL_UNSIGNED_INT, 0);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
