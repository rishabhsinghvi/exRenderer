#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;

out vec2 uvCoord;

void main()
{
	gl_Position = projMatrix * viewMatrix * vec4(pos.xyz, 1.0f);
	uvCoord = tex;
}
