#version 330 core
out vec4 FragColor;
in vec3 color;
uniform float offsetColor;
void main()
{
    FragColor = vec4(color.x * offsetColor, color.y * offsetColor, color.z * offsetColor, 1.0f);
}