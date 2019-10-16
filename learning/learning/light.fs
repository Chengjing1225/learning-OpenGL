#version 330 core
out vec4 FragColor;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;	//	观察者的世界坐标

in vec3 Normal;
in vec3 FragPos;

void main()
{

	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos-FragPos);

	float diff = max(dot(norm, lightDir),0.0);
	vec3 diffuse = diff * lightColor;	//漫反射

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos -FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);	//镜面反射

	float spec = pow(max(dot(viewDir,reflectDir),0.0),2);	//去32次幂，即高光的反光度
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse +specular) *objectColor;
    FragColor = vec4(result, 1.0);
}