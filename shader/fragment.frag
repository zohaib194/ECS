#version 330 core

in vec3 color;

out vec4 FragColor;


void main()
{
    FragColor = vec4(color.x * 1.0f, color.y * 0.5f, color.z * 0.2f, 1.0f);
} 