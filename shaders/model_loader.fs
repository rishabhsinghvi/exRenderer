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

#define NUM_LIGHTS 2

uniform Light light;
uniform vec3 modelColor;

uniform sampler2D diffuse0;
uniform sampler2D diffuse1;
uniform sampler2D diffuse2;
uniform sampler2D diffuse3;
uniform sampler2D diffuse4;

uniform sampler2D specular0;
uniform sampler2D specular1;
uniform sampler2D specular2;
uniform sampler2D specular3;
uniform sampler2D specular4;

void main()
{
	vec3 result;
	
	float ambientValue = 0.05;
	vec3 ambientColor = ambientValue * vec3(0.5,0.5,0.5);//texture(diffuse0, texCoords).rgb;

	vec3 normalizedNormal = normalize(normCoords);
	vec3 lightDir = normalize(light.lightPos - fragmentPos);

	float diffuseValue = max(dot(normalizedNormal, lightDir), 0.0);
	vec3 diffuseColor = diffuseValue * light.lightColor * vec3(0.5,0.5,0.5);//texture(diffuse0, texCoords).rgb;

	result = ambientColor+diffuseColor;
	
	frag_color = vec4(result, 1.0);
}