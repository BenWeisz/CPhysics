#ifndef VERTEX_ATTRIB_ARRAY_H
#define VERTEX_ATTRIB_ARRAY_H

#include <stdlib.h>

#include <util/types.h>
#include <util/log.h>

#define VERTEX_ATTRIB_FLOAT 0

typedef struct _VERTEX_ATTRIB {
    u32 type;
    u32 num_elements;
} _VERTEX_ATTRIB;

typedef struct VERTEX_ATTRIB_ARRAY {
    _VERTEX_ATTRIB* vertex_attribs;
    u32 vertex_attribs_length;
    u32 vertex_attribs_capacity;
} VERTEX_ATTRIB_ARRAY;

VERTEX_ATTRIB_ARRAY* VertexAttribArray_create(u32 num_vertex_attribs);
void VertexAttribArray_delete(const VERTEX_ATTRIB_ARRAY* vertex_attrib_array);

void VertexAttribArray_add_floats(VERTEX_ATTRIB_ARRAY* vertex_attrib_array, u32 type, u32 num_elements);

#endif  // VERTEX_ATTRIB_ARRAY_H