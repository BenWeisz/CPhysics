#version 410

layout (location = 0) in vec3 iPos;

void main()
{
    gl_Position = vec4(iPos, 1.0);
}
