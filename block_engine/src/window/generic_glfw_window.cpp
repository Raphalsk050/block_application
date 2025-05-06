#include "generic_glfw_window.h"

#include "../bepch.h"
#include "../event/event.h"
#include "../event/key_event.h"
#include "../event/mouse_event.h"
#include "../event/window_application_event.h"
#include "../renderer/renderer.h"

namespace BEngine {
  static uint8_t s_GLFWWindowCount = 0;

  static void GLFWErrorCallback(int error, const char *description) {
    BENGINE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
  }

  GenericWindow::GenericWindow(const WindowProps &props) {
    BENGINE_PROFILE_FUNCTION();

    GenericWindow::Init(props);
  }

  GenericWindow::~GenericWindow() {
    BENGINE_PROFILE_FUNCTION();

    Shutdown();
  }

  void GenericWindow::Init(const WindowProps &props) {
    BENGINE_PROFILE_FUNCTION();

    data_.Title = props.Title;
    data_.Width = props.Width;
    data_.Height = props.Height;

    BENGINE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width,
                      props.Height);

    if (s_GLFWWindowCount == 0) {
      BENGINE_PROFILE_SCOPE("glfwInit");
      int success = glfwInit();
      BENGINE_CORE_ASSERT(success, "Could not initialize GLFW!");
      glfwSetErrorCallback(GLFWErrorCallback);
    } {
      BENGINE_PROFILE_SCOPE("glfwCreateWindow");
#if defined(DEBUG)
      if (Renderer::GetAPI() == RendererAPI::API::OpenGL) {
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      }
#endif
      window_ = glfwCreateWindow((int) props.Width, (int) props.Height,
                                  data_.Title.c_str(), nullptr, nullptr);
      ++s_GLFWWindowCount;
    }

    context_ = GraphicsContext::Create(window_);
    context_->Init();

    glfwSetWindowUserPointer(window_, &data_);
    SetVSync(true);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(
      window_, [](GLFWwindow *window, int width, int height) {
        WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;

        WindowResizeEvent event(width, height);
        data.EventCallback(event);
      });

    glfwSetWindowCloseCallback(window_, [](GLFWwindow *window) {
      WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
      WindowCloseEvent event;
      data.EventCallback(event);
    });

    glfwSetKeyCallback(window_, [](GLFWwindow *window, int key, int scancode,
                                    int action, int mods) {
      WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

      switch (action) {
        case GLFW_PRESS: {
          KeyPressedEvent event(key, 0);
          data.EventCallback(event);
          break;
        }
        case GLFW_RELEASE: {
          KeyReleasedEvent event(key);
          data.EventCallback(event);
          break;
        }
        case GLFW_REPEAT: {
          KeyPressedEvent event(key, true);
          data.EventCallback(event);
          break;
        }
      }
    });

    glfwSetCharCallback(window_, [](GLFWwindow *window, unsigned int keycode) {
      WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

      KeyTypedEvent event(keycode);
      data.EventCallback(event);
    });

    glfwSetMouseButtonCallback(
      window_, [](GLFWwindow *window, int button, int action, int mods) {
        WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

        switch (action) {
          case GLFW_PRESS: {
            MouseButtonPressedEvent event(button);
            data.EventCallback(event);
            break;
          }
          case GLFW_RELEASE: {
            MouseButtonReleasedEvent event(button);
            data.EventCallback(event);
            break;
          }
        }
      });

    glfwSetScrollCallback(
      window_, [](GLFWwindow *window, double xOffset, double yOffset) {
        WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float) xOffset, (float) yOffset);
        data.EventCallback(event);
      });

    glfwSetCursorPosCallback(
      window_, [](GLFWwindow *window, double xPos, double yPos) {
        WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

        MouseMovedEvent event((float) xPos, (float) yPos);
        data.EventCallback(event);
      });
  }

  void GenericWindow::Shutdown() {
    BENGINE_PROFILE_FUNCTION();

    glfwDestroyWindow(window_);
    --s_GLFWWindowCount;

    if (s_GLFWWindowCount == 0) {
      glfwTerminate();
    }
  }

  void GenericWindow::OnUpdate() {
    BENGINE_PROFILE_FUNCTION();

    glfwPollEvents();
    context_->SwapBuffers();
  }

  void GenericWindow::SetVSync(bool enabled) {
    BENGINE_PROFILE_FUNCTION();

    if (enabled)
      glfwSwapInterval(1);
    else
      glfwSwapInterval(0);

    data_.VSync = enabled;
  }

  bool GenericWindow::IsVSync() const { return data_.VSync; }
} // namespace BEngine
