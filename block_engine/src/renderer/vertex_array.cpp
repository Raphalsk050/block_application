#include "block_engine/bepch.h"
#include "block_engine/src/renderer/vertex_array.h"

#include "block_engine/src/renderer/renderer.h"
#include "block_engine/src/platform/opengl/opengl_vertex_array.h"

namespace BEngine {

Ref<VertexArray> VertexArray::Create()
{
  switch (Renderer::GetAPI())
  {
    case RendererAPI::API::None:    BENGINE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
  }

  BENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

}