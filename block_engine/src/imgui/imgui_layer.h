#pragma once

#include "../event/key_event.h"
#include "../event/mouse_event.h"
#include "../event/window_application_event.h"
#include "../layer/layer.h"

namespace BEngine {
class ImGuiLayer : public Layer {
 public:
  ImGuiLayer();
  ~ImGuiLayer() = default;

  virtual void OnAttach() override;
  void OnUpdate(Timestep ts) override;
  virtual void OnDetach() override;
  virtual void OnEvent(Event& e) override;

  void Begin();
  void End();

  void BlockEvents(bool block) { block_events_ = block; }

  void SetDarkThemeColors();

  void ShowMetricsWindow();

  uint32_t GetActiveWidgetID() const;

 private:
  bool block_events_ = true;
};
}  // namespace BEngine