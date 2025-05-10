#include "render_command.h"

#include "../../bepch.h"

namespace BEngine {

  Scope<RendererAPI> RenderCommand::renderer_api_ = RendererAPI::Create();

}