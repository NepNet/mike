#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUv;

out VS_OUT{
    vec4 color;
    vec3 normal;
    vec3 position;
    vec2 uv;
}v2f;

layout(std140)
uniform Camera{
    mat4 projection;
    mat4 view;
};

uniform mat4 localToWorld;

void main()
{
    gl_Position = projection * view * localToWorld * vec4(aPos, 1.0);
    v2f.color = vec4(aPos + 0.5, 1);
    v2f.position = aPos;
    v2f.uv = aUv;
    v2f.normal = aNormal * mat3(transpose(inverse(localToWorld)));
}