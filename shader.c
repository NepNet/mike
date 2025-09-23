#include "shader.h"

#include <stddef.h>
#include <stdio.h>
#include <glad/glad.h>

ShaderHandle shaderCreate(const char *vertexSource, const char *fragmentSource) {
    const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    const ShaderHandle handle = glCreateProgram();

    glAttachShader(handle, vertexShader);
    glAttachShader(handle, fragmentShader);
    glLinkProgram(handle);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return handle;
}

void read_file(const char *path, char *buffer) {
    FILE *file = fopen(path, "r");
    fseek (file, 0, SEEK_END);
    const long length = ftell (file);
    fseek (file, 0, SEEK_SET);
    fread(buffer, 1, length, file);
    fclose(file);
}

Shader shader_load_from_file(const char *vertex_path, const char *fragment_path) {
    char vert_src[1024*1024];
    char frag_src[1024*1024];

    read_file(vertex_path, vert_src);
    read_file(fragment_path, frag_src);

    return shaderCreate(vert_src, frag_src);
}
