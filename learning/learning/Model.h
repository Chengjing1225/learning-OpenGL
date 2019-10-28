#ifndef  MODEL_H
#define MODEL_H
//#include "Shader.h"
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
 
#include <string>
#include <vector>

class Model
{
public:
	Model(string const &path, bool gamma = false);
	void Draw(Shader shader);

private:
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;

	void loadModel(string path);
	void processNode(aiNode* mesh, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};
#endif

