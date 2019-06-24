#version 330 core

out vec4 FragColor;

uniform sampler2D texture1;

in vec2 texCoord;

void main()
{
	FragColor = vec4(0.80784, 0.78431, 0.0,1.0);
}
