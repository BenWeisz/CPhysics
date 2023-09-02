#include "graphics/display/model.h"

MODEL* Model_create()
{
    MODEL* model = (MODEL*)malloc(sizeof(MODEL));
    if (model == NULL)
    {
        Log_error("Failed to allocate memory for MODEL\n");
        return NULL;
    }

    model->mesh = NULL;
    model->vertex_array = VertexArray_create();
    model->vertex_attrib_array = NULL;
}

// NOTE: THIS WILL DELETE THE MESH AND THE VERTEX_ATTRIB_ARRAY
void Model_delete(const MODEL* model)
{
    Mesh_delete(model->mesh);
    VertexArray_delete(model->vertex_array);
    VertexAttribArray_delete(model->vertex_attrib_array);

    free((void*)model);
}

void Model_set_mesh(MODEL* model, MESH* mesh)
{
    model->mesh = mesh;
}

void Model_set_vertex_attrib_array(MODEL* model, VERTEX_ATTRIB_ARRAY* vertex_attrib_array)
{
    model->vertex_attrib_array = vertex_attrib_array;
}

void Model_pack(const MODEL* model)
{
    VertexArray_bind(model->vertex_array);
    Mesh_bind(model->mesh);
    
    VertexArray_set_vertex_attribs(model->vertex_array, model->vertex_attrib_array);

    VertexArray_unbind();
}

void Model_draw(const MODEL* model)
{
    glDrawElements(GL_TRIANGLES, model->mesh->mesh_data->vertex_data_length, GL_UNSIGNED_INT, NULL);
}

void Model_bind(const MODEL* model)
{
    VertexArray_bind(model->vertex_array);
}

void Model_unbind()
{
    VertexArray_unbind();
}
