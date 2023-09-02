cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(CPhysics VERSION 1.0)

add_definitions(-std=c11)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(VENDOR_DIR "~/vendor")

add_executable(CPhysics main.c)

find_package(glfw3 3.3 REQUIRED)

target_include_directories(CPhysics PUBLIC include)
target_include_directories(CPhysics PUBLIC ${VENDOR_DIR}/glad-core-4.5/include)

target_link_libraries(CPhysics glfw ${OPENGL_opengl_LIBRARY})
target_link_libraries(CPhysics glfw ${OPENGL_glx_LIBRARY})

target_sources(CPhysics PUBLIC
    ${VENDOR_DIR}/glad-core-4.5/src/glad.c
    src/util/log.c
    src/util/io.c
    src/graphics/base/shader_program.c
    src/graphics/base/vertex_buffer.c
    src/graphics/base/index_buffer.c
    src/graphics/base/vertex_attrib_array.c
    src/graphics/base/vertex_array.c
    src/graphics/display/mesh.c
    src/graphics/display/model.c
)