#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uvCoords;

out vec2 texCoords;
out vec3 normCoords;
out vec3 fragmentPos;

uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

void main()
{
	fragmentPos = vec3(modelMatrix*vec4(pos, 1.0));
	normCoords = normalMatrix * normal;
	
	texCoords = uvCoords;    

     gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);
}