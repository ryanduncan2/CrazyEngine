#version 450

in vec4 v_Colour;
in vec2 v_TextureCoords;
flat in float v_TextureIndex;

out vec4 o_Colour;

uniform sampler2D u_Textures[32];

void main()
{
    o_Colour = texture(u_Textures[int(v_TextureIndex)], v_TextureCoords) * v_Colour;
}