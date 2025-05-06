#pragma once

#include "renderer_api.h"

namespace BEngine {
class Renderer {
 public:
  static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
};
}  // namespace BEngine
