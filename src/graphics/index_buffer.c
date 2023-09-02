#include "graphics/index_buffer.h"

INDEX_BUFFER* IndexBuffer_create()
{
    INDEX_BUFFER* index_buffer = (INDEX_BUFFER*)malloc(sizeof(INDEX_BUFFER));
    if (index_buffer == NULL)
    {
        Log_error("Failed to allocate memory for INDEX_BUFFER\n");
        return NULL;
    }

    glGenBuffers(1, &(index_buffer->ID));
    
    if (index_buffer == 0)
    {
        Log_error("Failed to generate INDEX_BUFFER handle\n");
        free((void*)index_buffer);
        return NULL;
    }

    return index_buffer;
}

void IndexBuffer_delete(const INDEX_BUFFER* index_buffer)
{
    glDeleteBuffers(1, &(index_buffer->ID));
    free((void*)index_buffer);
}

/* NOTE: MUST BIND VERTEX_BUFFER BEFORE CALLING */
void IndexBuffer_buffer_data(const u32* data, const u32 data_count)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * data_count, data, GL_STATIC_DRAW);
}

void IndexBuffer_bind(const INDEX_BUFFER* index_buffer)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->ID);
}

void IndexBuffer_unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}