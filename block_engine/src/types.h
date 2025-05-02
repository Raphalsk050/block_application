#pragma once
#include <glm/vec3.hpp>

namespace BEngine {
  // this is a 8x8 horizontal size
#define CHUNK_SIZE 8
#define CHUNK_HEIGHT_SIZE 512

  struct vertex {
    glm::vec3 position;
  };

  struct cube {
    vertex vertices[4];
  };

  struct chunk {
    cube cubes[CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT_SIZE];
  };
}
