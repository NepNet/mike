//
// Created by nepnet on 9/23/25.
//
#include "player.h"

#include <string.h>

PlayerData player_data;

PlayerData * player_get_player_data() {
	return &player_data;
}

void player_get_view(mat4 view) {
	memcpy(view, GLM_MAT4_IDENTITY, sizeof(mat4));

	if(player_data.pitch > 89.0f)
		player_data.pitch =  89.0f;
	if(player_data.pitch < -89.0f)
		player_data.pitch = -89.0f;

	vec3 cameraFront;
	cameraFront[0] = cos(player_data.yaw * 0.0174533f); // Note that we convert the angle to radians first
	cameraFront[2] = sin(player_data.yaw * 0.0174533f);
	cameraFront[1] = sin(player_data.pitch * 0.0174533f);

	glm_normalize(cameraFront);

	vec3 eye = {0};
	vec3 view_dir = {0};
	glm_vec3_add(player_data.position, (vec3){0.0f,1.0f,0.0f}, eye);
	glm_vec3_add(eye, cameraFront, view_dir);

	glm_lookat(eye, view_dir, (vec3){0.0f,1.0f,0.0f}, view);
}
