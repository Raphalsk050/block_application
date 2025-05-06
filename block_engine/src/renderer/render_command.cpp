#include "../bepch.h"
#include "render_command.h"

namespace BEngine {

  Scope<RendererAPI> RenderCommand::renderer_api_ = RendererAPI::Create();

}