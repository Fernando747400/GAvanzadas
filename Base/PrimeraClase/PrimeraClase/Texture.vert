#version 330 core

layout (location = 2) in vec2 aTex;
out vec2 texCoord;

void main()
{
texCoord = aTex;
}