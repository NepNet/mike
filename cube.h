//
// Created by nepnet on 28.09.2025.
//

#ifndef MIKE_CUBE_H
#define MIKE_CUBE_H

#define NORMAL_UP {0.0f, 1.0f, 0.0f}
#define NORMAL_DOWN {0.0f, -1.0f, 0.0f}
#define NORMAL_FRONT {0.0f, 0.0f, 1.0f}
#define NORMAL_BACK {0.0f, 0.0f, -1.0f}
#define NORMAL_LEFT {-1.0f, 0.0f, 0.0f}
#define NORMAL_RIGHT {1.0f, 0.0f, 0.0f}

struct vertex{
    float position[3], normal[3], uv[2];
};

struct vertex cube_vertices[] = {
    //front
    {{-0.5f, -0.5f, +0.5f}, NORMAL_FRONT, {0, 1}},
    {{+0.5f, -0.5f, +0.5f}, NORMAL_FRONT, {1, 1}},
    {{+0.5f, +0.5f, +0.5f}, NORMAL_FRONT, {1, 0}},
    {{-0.5f, +0.5f, +0.5f}, NORMAL_FRONT, {0, 0}},
    //back
    {{+0.5f, +0.5f, -0.5f}, NORMAL_BACK,  {1, 0}},
    {{+0.5f, -0.5f, -0.5f}, NORMAL_BACK,  {1, 1}},
    {{-0.5f, -0.5f, -0.5f}, NORMAL_BACK,  {0, 1}},
    {{-0.5f, +0.5f, -0.5f}, NORMAL_BACK,  {0, 0}},
    //right
    {{+0.5f, -0.5f, -0.5f}, NORMAL_RIGHT, {0, 1}},
    {{+0.5f, +0.5f, -0.5f}, NORMAL_RIGHT, {0, 0}},
    {{+0.5f, +0.5f, +0.5f}, NORMAL_RIGHT, {1, 0}},
    {{+0.5f, -0.5f, +0.5f}, NORMAL_RIGHT, {1, 1}},
    //left
    {{-0.5f, +0.5f, +0.5f}, NORMAL_LEFT,  {0, 0}},
    {{-0.5f, +0.5f, -0.5f}, NORMAL_LEFT,  {1, 0}},
    {{-0.5f, -0.5f, -0.5f}, NORMAL_LEFT,  {1, 1}},
    {{-0.5f, -0.5f, +0.5f}, NORMAL_LEFT,  {0, 1}},
    //top
    {{+0.5f, +0.5f, +0.5f}, NORMAL_UP,    {0, 1}},
    {{+0.5f, +0.5f, -0.5f}, NORMAL_UP,    {0, 0}},
    {{-0.5f, +0.5f, -0.5f}, NORMAL_UP,    {1, 0}},
    {{-0.5f, +0.5f, +0.5f}, NORMAL_UP,    {1, 1}},
    //bottom
    {{-0.5f, -0.5f, -0.5f}, NORMAL_DOWN, {0, 0}},
    {{+0.5f, -0.5f, -0.5f}, NORMAL_DOWN, {1, 0}},
    {{+0.5f, -0.5f, +0.5f}, NORMAL_DOWN, {1, 1}},
    {{-0.5f, -0.5f, +0.5f}, NORMAL_DOWN, {0, 1}},
};

const int cube_indices_count = 36;
unsigned int cube_indices[] = {
        //front
        0, 1, 2,
        0, 2, 3,
        //back
        4, 5, 6,
        4, 6, 7,
        //right
        8, 9, 10,
        8, 10, 11,
        //left
        12, 13, 14,
        12, 14, 15,
        //top
        16, 17, 18,
        16, 18, 19,
        //bottom
        20, 21, 22,
        20, 22, 23,
};

#endif //MIKE_CUBE_H
