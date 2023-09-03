#ifndef MESH_H
#define MESH_H

#include <stdlib.h>

#include "util/types.h"
#include "util/log.h"
#include "util/io.h"
#include "util/strings.h"

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
    u16 was_loaded_from_file;
} MESH;

MESH* Mesh_create();
void Mesh_delete(const MESH* mesh);

void Mesh_add_vertex_data(MESH* mesh, f32* data, const u32 data_length);
void Mesh_add_index_data(MESH* mesh, u32* data, const u32 data_length);

void Mesh_load_from_file(MESH* mesh, const char* filename);

/* NOTE: MUST BIND MESH BEFORE CALLING */ 
void Mesh_pack(MESH* mesh);

void Mesh_bind(const MESH* mesh);
void Mesh_unbind();

u16 _Mesh_parse_obj_source(MESH* mesh, const char* data);
const char* _Mesh_forward_to_next_token(MESH* mesh, const char* data, u32 line_number);

#endif  // MESH_H