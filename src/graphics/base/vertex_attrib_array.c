#include "graphics/base/vertex_attrib_array.h"

VERTEX_ATTRIB_ARRAY* VertexAttribArray_create(u32 num_vertex_attribs)
{
    VERTEX_ATTRIB_ARRAY* vertex_attrib_array = (VERTEX_ATTRIB_ARRAY*)malloc(sizeof(VERTEX_ATTRIB_ARRAY));
    if (vertex_attrib_array == NULL)
    {
        Log_error("Failed to allocate memory for VERTEX_ATTRIB_ARRAY\n");
        return NULL;
    }

    // Allocate space for the vertex attributes
    vertex_attrib_array->vertex_attribs = (_VERTEX_ATTRIB*)malloc(sizeof(_VERTEX_ATTRIB) * num_vertex_attribs);
    if (vertex_attrib_array->vertex_attribs == NULL)
    {
        Log_error("Failed to allocate memory for _VERTEX_ATTRIBs\n");
        free(vertex_attrib_array);
        return NULL;
    }

    vertex_attrib_array->vertex_attribs_length = 0;
    vertex_attrib_array->vertex_attribs_capacity = num_vertex_attribs;

    return vertex_attrib_array;
}

void VertexAttribArray_delete(const VERTEX_ATTRIB_ARRAY* vertex_attrib_array)
{
    free(vertex_attrib_array->vertex_attribs);
}

void VertexAttribArray_add_floats(VERTEX_ATTRIB_ARRAY* vertex_attrib_array, u32 type, u32 num_elements)
{
    if (num_elements < 1 || num_elements > 4)
    {
        Log_error("num_elements must be between 1 and 4 (inclusive)\n");
        return;
    }

    if (vertex_attrib_array->vertex_attribs_length >= vertex_attrib_array->vertex_attribs_capacity)
    {
        Log_error("Trying to add more attributes than defined at create time\n");
        return;
    }

    _VERTEX_ATTRIB* vertex_attrib = &(vertex_attrib_array->vertex_attribs[vertex_attrib_array->vertex_attribs_length]);

    vertex_attrib->type = type;
    vertex_attrib->num_elements = num_elements;

    vertex_attrib_array->vertex_attribs_length++;
}
