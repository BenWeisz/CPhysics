#include "graphics/display/mesh.h"

/* _MESH_SETUP */

_MESH_DATA* _MeshData_create()
{
    _MESH_DATA* mesh_setup = (_MESH_DATA*)malloc(sizeof(_MESH_DATA));
    if (mesh_setup == NULL)
    {
        Log_error("Failed to allocate memory for _MESH_DATA\n");
        return NULL;
    }

    mesh_setup->vertex_data = NULL;
    mesh_setup->vertex_data_length = 0;

    mesh_setup->index_data = NULL;
    mesh_setup->index_data_length = 0;

    return mesh_setup;
}

void _MeshData_delete(const _MESH_DATA* mesh_setup)
{
    free((void*)mesh_setup);
}

/* MESH */

MESH* Mesh_create()
{
    MESH* mesh = (MESH*)malloc(sizeof(MESH));
    if (mesh == NULL)
    {
        Log_error("Failed to allocate memory for MESH\n");
        return NULL;
    }

    mesh->mesh_data = (_MESH_DATA*)malloc(sizeof(_MESH_DATA));
    if (mesh->mesh_data == NULL)
    {
        Log_error("Failed to allocate memory for _MESH_DATA\n");
        free((void*)mesh);
        return NULL;
    }

    mesh->vertex_buffer = VertexBuffer_create();
    mesh->index_buffer = IndexBuffer_create();

    return mesh;
}

void Mesh_delete(const MESH* mesh)
{
    free((void*)mesh->mesh_data);
    
    VertexBuffer_delete(mesh->vertex_buffer);
    IndexBuffer_delete(mesh->index_buffer);

    free((void*)mesh);
}

void Mesh_add_vertex_data(MESH* mesh, f32* data, const u32 data_length)
{
    mesh->mesh_data->vertex_data = data;
    mesh->mesh_data->vertex_data_length = data_length;
}

void Mesh_add_index_data(MESH* mesh, u32* data, const u32 data_length)
{
    mesh->mesh_data->index_data = data;
    mesh->mesh_data->index_data_length = data_length;
}

/* NOTE: MUST BIND MESH BEFORE CALLING, HOLD ONTO BUFFER DATA POINTERS */ 
void Mesh_pack(MESH* mesh)
{
    // Buffer the vertex data
    VertexBuffer_buffer_data(mesh->mesh_data->vertex_data, mesh->mesh_data->vertex_data_length);

    // Buffer the index data
    IndexBuffer_buffer_data(mesh->mesh_data->index_data, mesh->mesh_data->index_data_length);

    // Free the MESH_DATA struct because we no longer need it
    free((void*)mesh->mesh_data);
    mesh->mesh_data = NULL;
}

void Mesh_bind(const MESH* mesh)
{
    VertexBuffer_bind(mesh->vertex_buffer);
    IndexBuffer_bind(mesh->index_buffer);
}

void Mesh_unbind()
{
    VertexBuffer_unbind();
    IndexBuffer_unbind();
}