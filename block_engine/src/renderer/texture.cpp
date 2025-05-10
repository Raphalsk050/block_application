#include "block_engine/src/renderer/texture.h"

#include "block_engine/bepch.h"
#include "block_engine/src/platform/opengl/opengl_texture.h"
#include "block_engine/src/renderer/renderer.h"

namespace BEngine {

Ref<Texture2D> Texture2D::Create(const TextureSpecification& specification) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      BENGINE_CORE_ASSERT(false,
                          "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateRef<OpenGLTexture2D>(specification);
  }

  BENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

Ref<Texture2D> Texture2D::Create(const std::string& path) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      BENGINE_CORE_ASSERT(false,
                          "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateRef<OpenGLTexture2D>(path);
  }

  BENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

}  // namespace BEngine