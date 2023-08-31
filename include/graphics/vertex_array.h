#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <stdlib.h>

#include <glad/glad.h>

#include "util/types.h"
#include "util/log.h"

#include "graphics/vertex_attrib_array.h"

typedef struct VERTEX_ARRAY {
    u32 ID;
    VERTEX_ATTRIB_ARRAY* vertex_attrib_array;
} VERTEX_ARRAY;

VERTEX_ARRAY* VertexArray_create(u32 num_vertex_attribs);
void VertexArray_delete(const VERTEX_ARRAY* vertex_array);

void VertexArray_bind(const VERTEX_ARRAY* vertex_array);
void VertexArray_unbind();

// NOTE: A call to this function assumes that bind was called before on this VERTEX_ARRAY
void VertexArray_set_vertex_attribs(VERTEX_ARRAY* vertex_array, VERTEX_ATTRIB_ARRAY* vertex_attrib_array);

#endif  // VERTEX_ARRAY_H