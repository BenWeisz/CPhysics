#ifndef MODEL_H
#define MODEL_H

#include <stdlib.h>

#include <glad/glad.h>

#include "util/types.h"
#include "util/log.h"

#include "graphics/base/vertex_array.h"
#include "graphics/base/vertex_attrib_array.h"

#include "graphics/display/mesh.h"

typedef struct MODEL {
    MESH* mesh;
    VERTEX_ARRAY* vertex_array;
    VERTEX_ATTRIB_ARRAY* vertex_attrib_array;
} MODEL;

MODEL* Model_create();

// NOTE: THIS WILL DELETE THE MESH AND THE VERTEX_ATTRIB_ARRAY
void Model_delete(const MODEL* model);

void Model_set_mesh(MODEL* model, MESH* mesh);
void Model_set_vertex_attrib_array(MODEL* model, VERTEX_ATTRIB_ARRAY* vertex_attrib_array);

void Model_pack(const MODEL* model);
void Model_draw(const MODEL* model);

void Model_bind(const MODEL* model);
void Model_unbind();

#endif  // MODEL_H