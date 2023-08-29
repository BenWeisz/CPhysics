#include <stdio.h>
#include <string.h>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "util/types.h"
#include "util/log.h"

#include "graphics/shader_program.h"

const u32 WIDTH = 800;
const u32 HEIGHT = 600;

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

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.169, 0.169, 0.49, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    // Stay tuned for part 2!

    return 0;
}