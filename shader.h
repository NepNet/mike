#ifndef SHADER_H
#define SHADER_H

typedef unsigned int ShaderHandle;
typedef ShaderHandle Shader;

ShaderHandle shaderCreate(const char *vertexSource, const char *fragmentSource);
Shader shader_load_from_file(const char *vertex_path, const char *fragment_path);

#endif //SHADER_H
