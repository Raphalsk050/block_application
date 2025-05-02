#include "../bepch.h"
#include "application.h"
#include "../log/belog.h"
#include "../timestep.h"
#include "../time.h"
#include "../debug/instrumentor.h"
#include "../input/input.h"

namespace BEngine {
  Application *Application::instance_ = nullptr;

  Application::Application(const ApplicationSpecification &specification)
    : specification_(specification) {
    BENGINE_PROFILE_FUNCTION();

    BENGINE_CORE_ASSERT(!instance_, "Application already exists!");
    instance_ = this;

    // Set working directory here
    if (!specification_.WorkingDirectory.empty())
      std::filesystem::current_path(specification_.WorkingDirectory);

    window_ = Window::Create(WindowProps(specification_.Name));
    window_->SetEventCallback(BENGINE_BIND_EVENT_FN(Application::OnEvent));

    //Renderer::Init();

    //m_ImGuiLayer = new ImGuiLayer();
    //PushOverlay(m_ImGuiLayer);
  }

  Application::~Application() {
    BENGINE_PROFILE_FUNCTION();

    //ScriptEngine::Shutdown();
    //Renderer::Shutdown();
  }

  // void Application::PushLayer(Layer *layer) {
  //   BENGINE_PROFILE_FUNCTION();
  //
  //   layer_stack.PushLayer(layer);
  //   layer->OnAttach();
  // }

  // void Application::PushOverlay(Layer *layer) {
  //   BENGINE_PROFILE_FUNCTION();
  //
  //   m_LayerStack.PushOverlay(layer);
  //   layer->OnAttach();
  // }

  void Application::Close() {
    running_ = false;
  }

  void Application::SubmitToMainThread(const std::function<void()> &function) {
    std::scoped_lock<std::mutex> lock(main_thread_queue_mutex_);

    main_thread_queue_.emplace_back(function);
  }

  void Application::OnEvent(Event &e) {
    BENGINE_PROFILE_FUNCTION();

    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BENGINE_BIND_EVENT_FN(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(BENGINE_BIND_EVENT_FN(Application::OnWindowResize));

    // for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
    //   if (e.Handled)
    //     break;
    //   (*it)->OnEvent(e);
    // }
  }

  void Application::Run() {
    BENGINE_PROFILE_FUNCTION();

    while (running_) {
      BENGINE_PROFILE_SCOPE("RunLoop");

      float time = Time::GetTime();
      Timestep timestep = time - last_frame_time_;
      last_frame_time_ = time;

      ExecuteMainThreadQueue();

      // if (!minimized_) {
      //   {
      //     BENGINE_PROFILE_SCOPE("LayerStack OnUpdate");
      //
      //     for (Layer *layer: m_LayerStack)
      //       layer->OnUpdate(timestep);
      //   }
      //
      //   m_ImGuiLayer->Begin(); {
      //     BENGINE_PROFILE_SCOPE("LayerStack OnImGuiRender");
      //
      //     for (Layer *layer: m_LayerStack)
      //       layer->OnImGuiRender();
      //   }
      //   m_ImGuiLayer->End();
      // }

      window_->OnUpdate();
    }
  }

  bool Application::OnWindowClose(WindowCloseEvent &e) {
    running_ = false;
    return true;
  }

  bool Application::OnWindowResize(WindowResizeEvent &e) {
    BENGINE_PROFILE_FUNCTION();

    if (e.GetWidth() == 0 || e.GetHeight() == 0) {
      minimized_ = true;
      return false;
    }

    minimized_ = false;
    //Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

    return false;
  }

  void Application::ExecuteMainThreadQueue() {
    std::scoped_lock<std::mutex> lock(main_thread_queue_mutex_);

    for (auto &func: main_thread_queue_)
      func();

    main_thread_queue_.clear();
  }
}
