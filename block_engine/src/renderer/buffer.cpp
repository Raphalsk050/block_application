#include "buffer.h"
#include "renderer.h"
#include "../platform/opengl/opengl_buffer.h"

namespace BEngine {
  Ref<VertexBuffer> VertexBuffer::Create(uint32_t size) {
    switch (Renderer::GetAPI()) {
      case RendererAPI::API::None: BENGINE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
      case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(size);
    }

    BENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

  Ref<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size) {
    switch (Renderer::GetAPI()) {
      case RendererAPI::API::None: BENGINE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
      case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);
    }

    BENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

  Ref<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t size) {
    switch (Renderer::GetAPI()) {
      case RendererAPI::API::None: BENGINE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
      case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, size);
    }

    BENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
} // BEngine
