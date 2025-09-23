#version 330 core
in vec4 col;
in vec3 Normal;
out vec4 FragColor;
void main()
{
	// diffuse
	vec3 direction = vec3(-1.0,-1.0,-1.0);

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1.0);
	vec3 ambient = vec3(0.1);

	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	FragColor = col;
	FragColor = vec4(diffuse * Normal + ambient, 1.0);
	FragColor = vec4(1.0);

	//FragColor = vec4(Normal, 1.0);
}