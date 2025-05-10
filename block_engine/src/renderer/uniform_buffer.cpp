#include "block_engine/bepch.h"
#include "block_engine/src/renderer/uniform_buffer.h"

#include "block_engine/src/renderer/renderer.h"
#include "block_engine/src/platform/opengl/uniform_buffer.h"

namespace BEngine {

Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
{
  switch (Renderer::GetAPI())
  {
    case RendererAPI::API::None:    BENGINE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL:  return CreateRef<OpenGLUniformBuffer>(size, binding);
  }

  BENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

}