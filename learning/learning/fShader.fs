#version 330 core
out vec4 FragColor;

struct Material {
<<<<<<< HEAD
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
}; 

struct Light {
   vec3 position;
    vec3 direction;
	float cutOff;		//聚光灯的切光角
	float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
	float linear;
	float quadratic;
=======
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
>>>>>>> parent of 86ec4fd... 2.4
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{	
	float distance = length(light.position - FragPos);
	 float attenuation = 1.0/(light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
	 vec3 lightDir = normalize(light.position - FragPos);

	float theta = dot(lightDir,normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);		//clamp把参数约束在了0.0-1.0之间
	
	// ambient
	vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
	
	// diffuse 
	vec3 norm = normalize(Normal);
<<<<<<< HEAD
		
	//vec3 lightDir = normalize(-light.direction);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
   
	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  
    
	
	diffuse *= intensity;
	specular *=intensity;   

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);
    
} 
=======
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
>>>>>>> parent of 86ec4fd... 2.4
