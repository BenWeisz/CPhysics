#include <stdio.h>
#include <string.h>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "util/types.h"
#include "util/log.h"

#include "graphics/base/shader_program.h"
#include "graphics/base/vertex_array.h"
#include "graphics/base/vertex_attrib_array.h"
#include "graphics/base/vertex_buffer.h"
#include "graphics/base/index_buffer.h"

#include "graphics/display/mesh.h"
#include "graphics/display/model.h"

const u32 WIDTH = 800;
const u32 HEIGHT = 600;

void input_handler(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

int main()
{
    if(!glfwInit()) {
        Log_error("Failed to init OpenGL\n");
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "CPhysics", NULL, NULL);
    if (window == NULL)
    {
        Log_error("Failed to create GLFW context\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    // Load all the references to the drive implementations for OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Log_error("Failed to load OpenGL implementations\n");
        return 1;   
    }

    SHADER_PROGRAM* shader_program = ShaderProgram_create("../res/shaders/base.vs", "../res/shaders/base.fs");

    f32 data[] = {
        -0.5, 0.5, 0.0,
        0.5, 0.5, 0.0,
        -0.5, -0.5, 0.0,
        0.5, -0.5, 0.0,
    };

    u32 index_data[] = {
        0, 2, 1,
        1, 2, 3
    };

    VERTEX_ATTRIB_ARRAY* vertex_attrib_array = VertexAttribArray_create(1);
    VertexAttribArray_add_floats(vertex_attrib_array, VERTEX_ATTRIB_FLOAT, 3);

    MESH* mesh = Mesh_create();
    Mesh_bind(mesh);
    Mesh_add_vertex_data(mesh, data, 12);
    Mesh_add_index_data(mesh, index_data, 6);
    Mesh_pack(mesh);

    MODEL* model = Model_create();
    Model_set_mesh(model, mesh);
    Model_set_vertex_attrib_array(model, vertex_attrib_array);

    Model_bind(model);
    Model_pack(model);
    Model_unbind();

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Input Handler
        input_handler(window);

        glClearColor(0.169, 0.169, 0.49, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw things here
        ShaderProgram_bind(shader_program);
        Model_bind(model);

        Model_draw(model);

        Model_unbind();
        ShaderProgram_unbind();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Model_delete(model);
    ShaderProgram_delete(shader_program);

    glfwTerminate();

    return 0;
}