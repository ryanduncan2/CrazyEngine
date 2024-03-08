#version 450 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Colour;
layout (location = 2) in vec2 a_TextureCoords;
layout (location = 3) in float a_TextureIndex;

out vec4 v_Colour;
out vec2 v_TextureCoords;
out float v_TextureIndex;

uniform mat4 u_Projection;

void main()
{
    v_Colour = a_Colour;
    v_TextureCoords = a_TextureCoords;
    v_TextureIndex = a_TextureIndex;

    gl_Position = u_Projection * vec4(a_Pos.x, a_Pos.y, a_Pos.z, 1.0);
}