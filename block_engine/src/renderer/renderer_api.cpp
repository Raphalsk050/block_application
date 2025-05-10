#include "renderer_api.h"

#include "../../bepch.h"
#include "../platform/opengl/opengl_renderer_api.h"

namespace BEngine {
  RendererAPI::API RendererAPI::api_ = API::OpenGL;

  Scope<RendererAPI> RendererAPI::Create()
  {
    switch (api_)
    {
      case RendererAPI::API::None:    BENGINE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
      case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
    }

    BENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
} // BEngine