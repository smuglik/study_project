#pragma once
#include <vector>
#include "Vertex.h"
#include "Shader.h"
#include "Model.h"
#include "func.h"
//#include <>

using namespace std;

class Mesh {
public:
  /*  Mesh Data  */
  vector<Vertex> vertices;
  vector<unsigned int> indices;
  vector<Texture> textures;
  /*  Functions  */
  Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
  void Draw(Shader shader);
private:
  /*  Render data  */
  unsigned int VAO, VBO, EBO;
  /*  Functions    */
  void setupMesh();
};




