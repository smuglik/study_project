#pragma once
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

using namespace std;

class Model
{
public:
 
  /*  Functions   */
  Model(char *path) {
    loadModel(path);
  };

  vector<Texture> textures_loaded;
  void Draw(Shader shader);
private:
  /*  Model Data  */
  vector<Mesh> meshes;
  string directory;
  /*  Functions   */
  void loadModel(string const &path);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,string typeName);
};




