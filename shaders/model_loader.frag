#version 330 core

out vec4 frag_color;

in vec2 texCoords;
in vec3 normCoords;
in vec3 fragmentPos;

struct Light
{
	vec3 lightPos;
	vec3 lightColor;
};

uniform Light light;
uniform vec3 modelColor;


void main()
{    
	float ambientValue = 0.05;
	vec3 ambientColor = ambientValue * light.lightColor;

	vec3 result;
	vec3 normalizedNormal = normalize(normCoords);
	vec3 lightDir = normalize(light.lightPos - fragmentPos);

	float diffuseValue = max(dot(normalizedNormal, lightDir), 0.0);
	vec3 diffuseColor = diffuseValue * light.lightColor;

	result = (diffuseColor + ambientColor) * modelColor;
	
    frag_color = vec4(result, 1.0);
}