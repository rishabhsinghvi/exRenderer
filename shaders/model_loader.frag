#version 330 core

out vec4 frag_color;

in vec2 texCoords;
in vec3 normCoords;
in vec3 fragmentPos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 modelColor;

void main()
{    
	float ambient = 0.1;
	vec3 ambientColor = ambient * lightColor;

	vec3 normalized = normalize(normCoords);
	vec3 lightDir = normalize(lightPos - fragmentPos);
	float diffuseIm = max(dot(normalized, lightDir), 0.0);
	vec3 diff = diffuseIm * lightColor;

	vec3 result = (ambientColor + diff) * modelColor;
    frag_color = vec4(result, 1.0);
}