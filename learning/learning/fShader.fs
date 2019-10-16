#version 330 core
out vec4 FragColor;

struct Material {
	//vec3 ambient;
	//vec3 diffuse;
	sampler2D diffuse;
	vec3 specular;
	float shininess;
};
struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;  
in vec2 TexCoords;

uniform vec3 objectColor;
// uniform vec3 lightColor;
uniform vec3 viewPos;	//	观察者的世界坐标
uniform Material material;
uniform Light light;


void main()
{
	vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords));

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position-FragPos);

	float diff = max(dot(norm, lightDir),0.0);
	vec3 diffuse =light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));	//漫反射

	vec3 viewDir = normalize(viewPos -FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);	//镜面反射

	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);	//去32次幂，即高光的反光度
	vec3 specular = light.specular* (spec * material.specular);

	vec3 result = (ambient + diffuse +specular) *objectColor;
    FragColor = vec4(result, 1.0);
}