#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
out vec4 col;
out vec3 Normal;

uniform Camera{
   mat4 projection;
   mat4 view;
};

uniform mat4 localToWorld;

void main()
{
   gl_Position = projection * view * localToWorld * vec4(aPos, 1.0);
   col = vec4(aPos + 0.5, 1);
   //Normal = aNormal;
   Normal = aNormal * mat3(transpose(inverse(localToWorld)));

}