#include "application.h"

#include "block_engine/bepch.h"
#include "block_engine/src/debug/instrumentor.h"
#include "block_engine/src/imgui/imgui_layer.h"
#include "block_engine/src/input/input.h"
#include "block_engine/src/log/belog.h"
#include "block_engine/src/renderer/renderer.h"
#include "block_engine/src/time.h"
#include "block_engine/src/timestep.h"

namespace BEngine {
Application* Application::instance_ = nullptr;

Application::Application(const ApplicationSpecification& specification)
    : specification_(specification) {
  BENGINE_PROFILE_FUNCTION();

  BENGINE_CORE_ASSERT(!instance_, "Application already exists!");
  instance_ = this;

  // Set working directory here
  if (!specification_.WorkingDirectory.empty())
    std::filesystem::current_path(specification_.WorkingDirectory);

  auto window_props = WindowProps(specification.Name, specification.Width,
                                  specification.Height);
  window_ = Window::Create(window_props);
  window_->SetEventCallback(BENGINE_BIND_EVENT_FN(Application::OnEvent));

  Renderer::Init();

#ifdef DEBUG
  imgui_layer_ = new ImGuiLayer();
  PushOverlay(imgui_layer_);
#endif
}

Application::~Application() {
  BENGINE_PROFILE_FUNCTION();

  //ScriptEngine::Shutdown();
  Renderer::Shutdown();
}

void Application::PushLayer(Layer* layer) {
  BENGINE_PROFILE_FUNCTION();

  layer_stack_.PushLayer(layer);
  layer->OnAttach();
}

void Application::PushOverlay(Layer* layer) {
  BENGINE_PROFILE_FUNCTION();

  layer_stack_.PushOverlay(layer);
  layer->OnAttach();
}

void Application::Close() { running_ = false; }

void Application::SubmitToMainThread(const std::function<void()>& function) {
  std::scoped_lock<std::mutex> lock(main_thread_queue_mutex_);

  main_thread_queue_.emplace_back(function);
}

void Application::OnEvent(Event& e) {
  BENGINE_PROFILE_FUNCTION();

  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(
      BENGINE_BIND_EVENT_FN(Application::OnWindowClose));
  dispatcher.Dispatch<WindowResizeEvent>(
      BENGINE_BIND_EVENT_FN(Application::OnWindowResize));

  for (auto it = layer_stack_.rbegin(); it != layer_stack_.rend(); ++it) {
    if (e.Handled) break;
    (*it)->OnEvent(e);
  }
}

void Application::Run() {
  BENGINE_PROFILE_FUNCTION();

  while (running_) {
    BENGINE_PROFILE_SCOPE("RunLoop");

    float time = Timer::GetTime();
    Timestep timestep = time - last_frame_time_;
    last_frame_time_ = time;

    ExecuteMainThreadQueue();

    if (!minimized_) {
      {
        BENGINE_PROFILE_SCOPE("LayerStack OnUpdate");

        for (Layer* layer : layer_stack_) layer->OnUpdate(timestep);
      }

      // Only enables in debug mode
      if (imgui_layer_) {
        imgui_layer_->Begin();
        {
          BENGINE_PROFILE_SCOPE("LayerStack OnImGuiRender");

          for (Layer* layer : layer_stack_) layer->OnImGuiRender();
        }
        imgui_layer_->End();
      }
    }

    window_->OnUpdate();
  }
}

bool Application::OnWindowClose(WindowCloseEvent& e) {
  running_ = false;
  return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e) {
  BENGINE_PROFILE_FUNCTION();

  if (e.GetWidth() == 0 || e.GetHeight() == 0) {
    minimized_ = true;
    return false;
  }

  minimized_ = false;
  // Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
  BENGINE_CORE_TRACE("Window resized to: ({},{})", e.GetWidth(), e.GetHeight());
  return false;
}

void Application::ExecuteMainThreadQueue() {
  std::scoped_lock<std::mutex> lock(main_thread_queue_mutex_);

  for (auto& func : main_thread_queue_) func();

  main_thread_queue_.clear();
}
}  // namespace BEngine
