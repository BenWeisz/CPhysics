#include "graphics/vertex_buffer.h"

VERTEX_BUFFER* VertexBuffer_create()
{
    VERTEX_BUFFER* vertex_buffer = (VERTEX_BUFFER*)malloc(sizeof(VERTEX_BUFFER));
    if (vertex_buffer == NULL)
    {
        Log_error("Failed to allocate memory for new VERTEX_BUFFER\n");
        return NULL;
    }
    
    // Create a handle for the new buffer
    glGenBuffers(1, &(vertex_buffer->ID));

    if (vertex_buffer->ID == 0)
    {
        Log_error("Failed to create VERTEX_BUFFER\n");
        
        free((void*)vertex_buffer);
        return NULL;
    }

    return vertex_buffer;
}

void VertexBuffer_delete(const VERTEX_BUFFER* vertex_buffer)
{
    glDeleteBuffers(1, &(vertex_buffer->ID));
    free((void*)vertex_buffer);
}

/* NOTE: MUST BIND VERTEX_BUFFER BEFORE CALLING */
void VertexBuffer_buffer_data(const f32* data, const u32 data_count)
{
    glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * data_count, data, GL_DYNAMIC_DRAW);
}

void VertexBuffer_bind(const VERTEX_BUFFER* vertex_buffer)
{
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->ID);
}

void VertexBuffer_unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}