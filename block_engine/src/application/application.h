#pragma once
#include "block_engine/bepch.h"
#include "block_engine/src/event/window_application_event.h"
#include "block_engine/src/layer/layer.h"
#include "block_engine/src/layer/layer_stack.h"
#include "block_engine/src/window/window.h"

using namespace std;

namespace BEngine {
class ImGuiLayer;
struct ApplicationCommandLineArgs {
  int Count = 0;
  char **Args = nullptr;

  const char *operator[](int index) const {
    BENGINE_CORE_ASSERT(index < Count);
    return Args[index];
  }
};

struct ApplicationSpecification {
  string Name = "Block engine Application";
  string WorkingDirectory;
  unsigned int Width = 1280;
  unsigned int Height = 720;
  ApplicationCommandLineArgs CommandLineArgs;
};

class Application {
 public:
  Application(const ApplicationSpecification &specification);

  virtual ~Application();

  void OnEvent(Event &e);

  void PushLayer(Layer *layer);

  void PushOverlay(Layer *layer);

  Window &GetWindow() const { return *window_; }

  void Close();

  // ImGuiLayer *GetImGuiLayer() { return imgui_layer_; }

  static Application &Get() { return *instance_; }

  const ApplicationSpecification &GetSpecification() const {
    return specification_;
  }

  void SubmitToMainThread(const function<void()> &function);

 public:
  void Run();

  bool OnWindowClose(WindowCloseEvent &e);

  bool OnWindowResize(WindowResizeEvent &e);

  void ExecuteMainThreadQueue();

 private:
  ApplicationSpecification specification_;
  Scope<Window> window_;
  ImGuiLayer *imgui_layer_;
  bool running_ = true;
  bool minimized_ = false;
  LayerStack layer_stack_;
  float last_frame_time_ = 0.0f;

  vector<function<void()> > main_thread_queue_;
  mutex main_thread_queue_mutex_;

 private:
  static Application *instance_;
};

Application *CreateApplication(ApplicationCommandLineArgs args);
}  // namespace BEngine
