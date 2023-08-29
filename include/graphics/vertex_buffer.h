#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <stdlib.h>

#include <glad/glad.h>

#include "util/types.h"
#include "util/log.h"

typedef struct VERTEX_BUFFER {
    u32 ID;
} VERTEX_BUFFER;

VERTEX_BUFFER* VertexBuffer_create();
void VertexBuffer_deinit(const VERTEX_BUFFER* vertex_buffer);

/* NOTE: MUST BIND VERTEX_BUFFER BEFORE CALLING */
void VertexBuffer_buffer_data(const f32* data, const u32 data_count);

void VertexBuffer_bind(const VERTEX_BUFFER* vertex_buffer);
void VertexBuffer_unbind();

#endif  // VERTEX_BUFFER_H