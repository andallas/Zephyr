#version 330 core

out vec4 color;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct Light
{
	vec3 position; // Not needed for directional light
	vec3 direction; // Not needed for point light
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float cutOff;
	float constant;
	float linear;
	float quadratic;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
	vec3 lightDir = normalize(light.position - FragPos); // Not used with directional lights
	//vec3 lightDir = normalize(-light.direction); // Use light.direction direction for directional light

	// Ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	// Emission
	vec3 emission = vec3(texture(material.emission, TexCoords));

	float theta = dot(lightDir, normalize(-light.direction));
	//float epsilon = light.cutOff - light.outerCutOff;
	//float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	if(theta > light.cutOff)
	{
		// Diffuse
		vec3 norm = normalize(Normal);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

		// Specular
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

		// Attenuation
		float lightRange = length(light.position - FragPos);
		float attenuation = 1.0f / (light.constant + light.linear * lightRange + light.quadratic * (lightRange * lightRange));

		//ambient *= attenuation; // No ambient attenuation with spotlights
		diffuse *= attenuation;
		specular *= attenuation;

		// Final
		color = vec4(ambient + diffuse + specular + emission, 1.0f);
	}
	else
	{
		// Final
		color = vec4(ambient + emission, 1.0f);
	}
	
}