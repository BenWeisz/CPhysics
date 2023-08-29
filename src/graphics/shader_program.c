#include "graphics/shader_program.h"

SHADER_PROGRAM* ShaderProgram_create(const char* vs_path, const char* fs_path)
{
    SHADER_PROGRAM* shader_program = (SHADER_PROGRAM*)malloc(sizeof(SHADER_PROGRAM));
    if (shader_program == NULL)
    {
        Log_error("Failed to allocate memory for new SHADER_PROGRAM\n");
        return NULL;
    }

    shader_program->vs_ID = _ShaderProgram_create_shader(vs_path, SHADER_PROGRAM_VERTEX_SHADER);
    if (shader_program->vs_ID == 0)
    {
        free((void*)shader_program);
        return NULL;
    }

    shader_program->fs_ID = _ShaderProgram_create_shader(fs_path, SHADER_PROGRAM_FRAGMENT_SHADER);
    if (shader_program->fs_ID == 0)
    {
        glDeleteShader(shader_program->vs_ID);
        free((void*)shader_program);
        return NULL;
    }

    // Create the new program
    shader_program->ID = glCreateProgram();

    // Attach the shaders
    glAttachShader(shader_program->ID, shader_program->vs_ID);
    glAttachShader(shader_program->ID, shader_program->fs_ID);

    // Link the program
    glLinkProgram(shader_program->ID);
    
    // Error checking
    i32 did_link;
    glGetProgramiv(shader_program->ID, GL_LINK_STATUS, &did_link);
    if (did_link != GL_TRUE)
    {
        i32 log_length;
        char message[1024];
        glGetProgramInfoLog(shader_program->ID, 1024, &log_length, message);
        
        Log_error("Failed to link shader program:\n%s\n", message);
        
        glDeleteShader(shader_program->vs_ID);
        glDeleteShader(shader_program->fs_ID);

        free((void*)shader_program);

        return NULL;
    }

    // Mark for delete
    glDeleteShader(shader_program->vs_ID);
    glDeleteShader(shader_program->fs_ID);

    return shader_program;
}

void ShaderProgram_deinit(const SHADER_PROGRAM* shader_program)
{
    // Detach individual shaders
    glDetachShader(shader_program->ID, shader_program->vs_ID);
    glDetachShader(shader_program->ID, shader_program->fs_ID);

    glDeleteProgram(shader_program->ID);

    free((void*)shader_program);
}

u32 _ShaderProgram_create_shader(const char* path, u32 type)
{
    const char* shader_src = IO_read(path);
    if (shader_src == NULL)
    {
        Log_error("Failed to read shader source: %s\n", path);
        return 0;
    }

    u32 shader_id;
    if (type == SHADER_PROGRAM_VERTEX_SHADER)
    {
        shader_id = glCreateShader(GL_VERTEX_SHADER);
    } 
    else if (type == SHADER_PROGRAM_FRAGMENT_SHADER)
    {
        shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    }
    else
    {
        Log_error("Wrong type was specified for call to _ShaderProgram_create_shader\n");
        free((void*)shader_src);
        return 0;
    }

    // Set the shader source
    glShaderSource(shader_id, 1, &shader_src, NULL);

    // Compile the shader
    glCompileShader(shader_id);
    
    // Check for errors
    i32 did_compile;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &did_compile);
    if (did_compile != GL_TRUE)
    {
        i32 log_length;
        char message[1024];
        glGetShaderInfoLog(shader_id, 1024, &log_length, message);
        
        Log_error("Failed to compile shader: %s\n%s\n", path, message);
        
        free((void*)shader_src);
        return 0;
    }

    free((void*)shader_src);
    return shader_id;
}