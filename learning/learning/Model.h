#ifndef MODEL_H_
#define MODEL_H_

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>

#include "Mesh.h"

class Model{
public:
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;
	bool gammaCorrection;
	Model(const char* path, bool gamma = false):gammaCorrection(gamma) {
		loadModel(path);
	}

	void Draw(Shader shader);

private:	
	void loadModel(std::string path);
	unsigned int loadCubemap(vector<std::string> faces);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialtextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif
