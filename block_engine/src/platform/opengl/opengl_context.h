#pragma once
#include "../../renderer/graphics_context.h"


struct GLFWwindow;

namespace BEngine {
  class OpenGLContext : public GraphicsContext {
  public:
    OpenGLContext(GLFWwindow *windowHandle);

    virtual void Init() override;

    virtual void SwapBuffers() override;

  private:
    GLFWwindow *window_handle_;
  };
}
