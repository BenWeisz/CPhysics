#ifndef MESH_H
#define MESH_H

#include <stdlib.h>

#include "util/types.h"
#include "util/log.h"

#include "graphics/base/vertex_buffer.h"
#include "graphics/base/index_buffer.h"

typedef struct _MESH_DATA {
    f32* vertex_data;
    u32 vertex_data_length;
    u32* index_data;
    u32 index_data_length;
} _MESH_DATA;

_MESH_DATA* _MeshData_create();
void _MeshData_delete(const _MESH_DATA* mesh_setup);

typedef struct MESH {
    _MESH_DATA* mesh_data;
    VERTEX_BUFFER* vertex_buffer;
    INDEX_BUFFER* index_buffer;
} MESH;

MESH* Mesh_create();
void Mesh_delete(const MESH* mesh);

void Mesh_add_vertex_data(MESH* mesh, f32* data, const u32 data_length);
void Mesh_add_index_data(MESH* mesh, u32* data, const u32 data_length);

/* NOTE: MUST BIND MESH BEFORE CALLING */ 
void Mesh_pack(MESH* mesh);

void Mesh_bind(const MESH* mesh);
void Mesh_unbind();

#endif  // MESH_H