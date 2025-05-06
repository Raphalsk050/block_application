#pragma once
#include "src/block_engine.h"

class GenericLayer : public BEngine::Layer {
public:
  GenericLayer();

  virtual ~GenericLayer() = default;

  void OnAttach() override;
  void OnDetach() override;

  void OnUpdate(BEngine::Timestep ts) override;
  void OnImGuiRender() override;
  void OnEvent(BEngine::Event& e) override;

private:
  glm::vec4 square_color_ = { 0.2f, 0.3f, 0.8f, 1.0f};
};
