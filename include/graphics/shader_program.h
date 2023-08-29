#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <stdlib.h>

#include <glad/glad.h>

#include "util/types.h"
#include "util/io.h"

#define SHADER_PROGRAM_VERTEX_SHADER 0
#define SHADER_PROGRAM_FRAGMENT_SHADER 1

typedef struct SHADER_PROGRAM {
    u32 ID;
    u32 vs_ID;
    u32 fs_ID;
} SHADER_PROGRAM;

SHADER_PROGRAM* ShaderProgram_create(const char* vs_path, const char* fs_path);
void ShaderProgram_deinit(const SHADER_PROGRAM* shader_program);

u32 _ShaderProgram_create_shader(const char* path, u32 type);

#endif  // SHADER_PROGRAM_H