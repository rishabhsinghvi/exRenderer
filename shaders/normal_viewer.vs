#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 uvCoords;

out VS_OUT {
    vec3 normal;
} vs_out;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
//uniform mat3 normalMatrix;

void main()
{
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0); 
    mat3 normalMatrix = mat3(transpose(inverse(viewMatrix * modelMatrix)));
    vs_out.normal = normalize(vec3(projMatrix * vec4(normalMatrix * norm, 0.0)));
}