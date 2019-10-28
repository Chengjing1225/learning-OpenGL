#ifndef MESH_H
#define MESH_H
//#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
#include <vector>
using namespace std;
struct Vertex
{	
	glm::vec3 Normal;
	glm::vec3 Position;
	glm::vec2 TexCoords;
	/*glm::vec3 Tangent;
	glm::vec3 Bitangent;*/
};

struct Texture {
	unsigned int id;
	string type;
	string path;
};

class Mesh
{
public:
	vector<Vertex> vertices;
	vector<unsigned int > indices;
	vector<Texture> textures;
	unsigned int VAO;

	Mesh(vector<Vertex> vertices, vector<unsigned int > indices, vector<Texture> textures);
	void Draw(Shader shader);
private:
	unsigned int  VBO, EBO;
	void setupMesh();
};
#endif // !MESH_H



