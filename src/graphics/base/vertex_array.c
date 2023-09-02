#include "graphics/base/vertex_array.h"

VERTEX_ARRAY* VertexArray_create()
{
    VERTEX_ARRAY* vertex_array = (VERTEX_ARRAY*)malloc(sizeof(VERTEX_ARRAY));
    if (vertex_array == NULL)
    {
        Log_error("Failed to allocate memory for VERTEX_ARRAY\n");
        return NULL;
    }

    // Generate a new OpenGL Vertex Array
    glGenVertexArrays(1, &(vertex_array->ID));
    if (vertex_array->ID == 0)
    {
        Log_error("Failed to create VERTEX_ARRAY\n");
        free(vertex_array);
        return NULL;
    }

    vertex_array->vertex_attrib_array = NULL;

    return vertex_array;
}

void VertexArray_delete(const VERTEX_ARRAY* vertex_array)
{
    glDeleteVertexArrays(1, &(vertex_array->ID));
    free((void*)vertex_array);
}

void VertexArray_bind(const VERTEX_ARRAY* vertex_array)
{
    glBindVertexArray(vertex_array->ID);
}

void VertexArray_unbind()
{
    glBindVertexArray(0);
}

// NOTE: A call to this function assumes that bind was called before on this VERTEX_ARRAY
void VertexArray_set_vertex_attribs(VERTEX_ARRAY* vertex_array, VERTEX_ATTRIB_ARRAY* vertex_attrib_array)
{
    if (vertex_attrib_array->vertex_attribs_length != vertex_attrib_array->vertex_attribs_capacity)
    {
        Log_error("You must specify all of the vertex attributes in the VERTEX_ATTRIB_ARRAY\n");
        return;
    }

    vertex_array->vertex_attrib_array = vertex_attrib_array;

    u32 stride = 0;
    for (i32 i = 0; i < vertex_attrib_array->vertex_attribs_length; i++)
    {
        _VERTEX_ATTRIB* vertex_attrib = &(vertex_attrib_array->vertex_attribs[i]);
        if (vertex_attrib->type == VERTEX_ATTRIB_FLOAT)
        {
            stride += sizeof(f32) * vertex_attrib->num_elements; 
        }
    }

    u32 offset = 0;
    for (i32 i = 0; i < vertex_attrib_array->vertex_attribs_length; i++)
    {
        _VERTEX_ATTRIB* vertex_attrib = &(vertex_attrib_array->vertex_attribs[i]);
        if (vertex_attrib->type == VERTEX_ATTRIB_FLOAT)
        {
            glVertexAttribPointer(i, vertex_attrib->num_elements, GL_FLOAT, GL_FALSE, stride, (void*)(u64)offset);
            glEnableVertexAttribArray(i);
            offset += sizeof(f32) * vertex_attrib->num_elements; 
        }
    }
}