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
    mesh->was_loaded_from_file = CPHYSICS_FALSE;

    return mesh;
}

void Mesh_delete(const MESH* mesh)
{
    if (mesh->was_loaded_from_file)
    {
        free((void*)mesh->mesh_data->vertex_data);
        free((void*)mesh->mesh_data->index_data);
    }

    free((void*)mesh->mesh_data);
    
    VertexBuffer_delete(mesh->vertex_buffer);
    IndexBuffer_delete(mesh->index_buffer);

    free((void*)mesh);
}

void Mesh_add_vertex_data(MESH* mesh, f32* data, const u32 data_length)
{
    mesh->mesh_data->vertex_data = data;
    mesh->mesh_data->vertex_data_length = data_length;
    mesh->was_loaded_from_file = CPHYSICS_FALSE;
}

void Mesh_add_index_data(MESH* mesh, u32* data, const u32 data_length)
{
    mesh->mesh_data->index_data = data;
    mesh->mesh_data->index_data_length = data_length;
    mesh->was_loaded_from_file = CPHYSICS_FALSE;
}

void Mesh_load_from_file(MESH* mesh, const char* filename)
{
    u64 filename_size = strlen(filename);
    const char* filename_ending = filename + (filename_size - 4);
    if (strncmp(filename_ending, ".obj", 4) != 0)
    {
        Log_error("The source file for the MESH objects must be a .obj file\n");
        return;
    }
    
    const char* obj_source = IO_read(filename);
    if (obj_source == NULL)
        return;

    u16 status = _Mesh_parse_obj_source(mesh, obj_source);

    mesh->was_loaded_from_file = CPHYSICS_TRUE;
    free((void*)obj_source);
}

/* NOTE: MUST BIND MESH BEFORE CALLING */ 
void Mesh_pack(MESH* mesh)
{
    // Buffer the vertex data
    VertexBuffer_buffer_data(mesh->mesh_data->vertex_data, mesh->mesh_data->vertex_data_length);

    // Buffer the index data
    IndexBuffer_buffer_data(mesh->mesh_data->index_data, mesh->mesh_data->index_data_length);
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

u16 _Mesh_parse_obj_source(MESH* mesh, const char* data)
{
    // Get some metrics on the file
    const char* curr_char = data;

    mesh->mesh_data->vertex_data_length = 0;
    mesh->mesh_data->index_data_length = 0;
    while (curr_char != NULL && *curr_char != '\0')
    {
        if (*curr_char == 'v')
        {
            mesh->mesh_data->vertex_data_length += 3;
        }
        else if (*curr_char == 'f')
        {
            mesh->mesh_data->index_data_length += 3;
        }

        curr_char = Strings_get_next_line(curr_char);
    }

    mesh->mesh_data->vertex_data = (f32*)malloc(sizeof(f32) * mesh->mesh_data->vertex_data_length);
    if (mesh->mesh_data->vertex_data == NULL)
    {
        Log_error("Failed to allocate memory for vertex_data\n");
        return CPHYSICS_FAILURE;
    }

    mesh->mesh_data->index_data = (u32*)malloc(sizeof(u32) * mesh->mesh_data->index_data_length);
    if (mesh->mesh_data->index_data == NULL)
    {
        Log_error("Failed to allocate memory for index_data\n");
        free((void*)mesh->mesh_data->vertex_data);
        return CPHYSICS_FAILURE;
    }

    curr_char = data;
    u64 line_number = 0;
    u32 vertex_data_index = 0;
    u32 index_data_index = 0;
    while (curr_char != NULL && *curr_char != '\0')
    {
        if (*curr_char == 'v')
        {
            curr_char = _Mesh_forward_to_next_token(mesh, curr_char, line_number);
            if (curr_char == NULL) return CPHYSICS_FAILURE;
            mesh->mesh_data->vertex_data[vertex_data_index++] = atof(curr_char);

            curr_char = _Mesh_forward_to_next_token(mesh, curr_char, line_number);
            if (curr_char == NULL) return CPHYSICS_FAILURE;
            mesh->mesh_data->vertex_data[vertex_data_index++] = atof(curr_char);

            curr_char = _Mesh_forward_to_next_token(mesh, curr_char, line_number);
            if (curr_char == NULL) return CPHYSICS_FAILURE;
            mesh->mesh_data->vertex_data[vertex_data_index++] = atof(curr_char);
        }
        else if (*curr_char == 'f')
        {
            curr_char = _Mesh_forward_to_next_token(mesh, curr_char, line_number);
            if (curr_char == NULL) return CPHYSICS_FAILURE;
            mesh->mesh_data->index_data[index_data_index++] = atoi(curr_char) - 1;

            curr_char = _Mesh_forward_to_next_token(mesh, curr_char, line_number);
            if (curr_char == NULL) return CPHYSICS_FAILURE;
            mesh->mesh_data->index_data[index_data_index++] = atoi(curr_char) - 1;

            curr_char = _Mesh_forward_to_next_token(mesh, curr_char, line_number);
            if (curr_char == NULL) return CPHYSICS_FAILURE;
            mesh->mesh_data->index_data[index_data_index++] = atoi(curr_char) - 1;
        }

        curr_char = Strings_get_next_line(curr_char);
        line_number++;
    }

    return CPHYSICS_SUCCESS;
}

const char* _Mesh_forward_to_next_token(MESH* mesh, const char* data, u32 line_number)
{
    const char* curr_char = data;
    while (*curr_char != ' ')
    {
        curr_char = Strings_get_next_token(curr_char, ' ');
        if (*curr_char == 'v' || *curr_char == 'f' || *curr_char == '\n')
        {
            Log_error("Failed to parse obj file (Line %d)\n", line_number);
            free((void*)mesh->mesh_data->vertex_data);
            free((void*)mesh->mesh_data->index_data);
            return NULL;
        }
        else if (*curr_char != ' ')
        {
            break;
        }
    }

    return curr_char;
}