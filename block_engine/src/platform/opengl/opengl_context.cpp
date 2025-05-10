#include "opengl_context.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "block_engine/bepch.h"

namespace BEngine {
OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
    : window_handle_(windowHandle) {
  BENGINE_CORE_ASSERT(windowHandle, "Window handle is null!")
}

void OpenGLContext::Init() {
  BENGINE_PROFILE_FUNCTION();

  glfwMakeContextCurrent(window_handle_);
  int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
  BENGINE_CORE_ASSERT(status, "Failed to initialize Glad!");

  BENGINE_CORE_INFO("OpenGL Info:");
  BENGINE_CORE_INFO("  Vendor: {}", (const char*)glGetString(GL_VENDOR));
  BENGINE_CORE_INFO("  Renderer: {}", (const char*)glGetString(GL_RENDERER));
  BENGINE_CORE_INFO("  Version: {}", (const char*)glGetString(GL_VERSION));

  // TODO: Fix this check
  BENGINE_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 &&
  GLVersion.minor >= 5),
                 "Block engine requires at least OpenGL version 4.5!");
}

void OpenGLContext::SwapBuffers() {
  BENGINE_PROFILE_FUNCTION();

  glfwSwapBuffers(window_handle_);
}
}  // namespace BEngine
