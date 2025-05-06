#pragma once

#include <GLFW/glfw3.h>

#include "../renderer/graphics_context.h"
#include "window.h"

namespace BEngine {

class GenericWindow : public Window {
 public:
  GenericWindow(const WindowProps& props);
  virtual ~GenericWindow();

  void OnUpdate() override;

  unsigned int GetWidth() const override { return m_Data.Width; }
  unsigned int GetHeight() const override { return m_Data.Height; }

  // Window attributes
  void SetEventCallback(const EventCallbackFn& callback) override {
    m_Data.EventCallback = callback;
  }
  void SetVSync(bool enabled) override;
  bool IsVSync() const override;

  virtual void* GetNativeWindow() const { return m_Window; }

 private:
  virtual void Init(const WindowProps& props);
  virtual void Shutdown();

 private:
  GLFWwindow* m_Window;
  Scope<GraphicsContext> m_Context;

  struct WindowData {
    std::string Title;
    unsigned int Width, Height;
    bool VSync;

    EventCallbackFn EventCallback;
  };

  WindowData m_Data;
};

}  // namespace BEngine