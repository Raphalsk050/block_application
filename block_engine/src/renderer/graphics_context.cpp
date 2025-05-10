#include "graphics_context.h"

#include "../../bepch.h"
#include "../platform/opengl/opengl_context.h"
#include "renderer.h"

namespace BEngine {
  Scope<GraphicsContext> GraphicsContext::Create(void* window)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::None:    BENGINE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
      case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
    }

    BENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
} // BEngine