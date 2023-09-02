#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <stdlib.h>

#include <glad/glad.h>

#include "util/types.h"
#include "util/log.h"

typedef struct INDEX_BUFFER {
    u32 ID;
} INDEX_BUFFER;

INDEX_BUFFER* IndexBuffer_create();
void IndexBuffer_delete(const INDEX_BUFFER* index_buffer);

/* NOTE: MUST BIND VERTEX_BUFFER BEFORE CALLING */
void IndexBuffer_buffer_data(const u32* data, const u32 data_count);

void IndexBuffer_bind(const INDEX_BUFFER* index_buffer);
void IndexBuffer_unbind();

#endif  // INDEX_BUFFER_H