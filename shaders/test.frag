#version 330 core

out vec4 FragColor;

uniform sampler2D texture1;

in vec2 uvCoord;

void main()
{
	FragColor = vec4(1.0,1.0,1.0,1.0);
}
