#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 uvCoords;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;

void main()
{
    uvCoords = aPos;
    vec4 pos = projMatrix * viewMatrix * vec4(aPos, 1.0);
	gl_Position = pos.xyww;
}  

