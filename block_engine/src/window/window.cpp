#include "window.h"
#include "generic_glfw_window.h"

namespace BEngine {
  Scope<Window> Window::Create(const WindowProps &props) {
#ifdef BENGINE_PLATFORM_APPLE
    return CreateScope<GenericWindow>(props);
#else
    BENGINE_CORE_ASSERT(false, "Unknown platform!");
    return nullptr;
#endif
  }
}
