//
// Created by nepnet on 9/23/25.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "cglm/cglm.h"

struct{
	float pitch, yaw;
	vec3 position;
}typedef PlayerData;

PlayerData* player_get_player_data();

void player_get_view(mat4 view);

#endif //PLAYER_H
