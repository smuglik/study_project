#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
/*
структуры  С Vertex и Texture
*/

using namespace glm;
using namespace std;

struct Vertex {
  vec3 Position;
  vec3 Normal;
  vec2 TexCoords;
};

struct Texture {
  unsigned int id;
  string type;
  string path;
};
