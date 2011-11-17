#version 330 core

uniform mat4 WorldViewProjMatrix;

in vec3 VertexPosition;
in vec3 VertexColor;

out vec3 Interpoled;

invariant gl_Position;

void main()
{
    Interpoled = VertexColor;

    gl_Position = WorldViewProjMatrix * vec4(VertexPosition, 1.0);
}
