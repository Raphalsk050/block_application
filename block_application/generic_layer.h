#pragma once

#include "block_engine/src/block_engine.h"

class GenericLayer : public BEngine::Layer
{
public:
  GenericLayer();
  virtual ~GenericLayer() = default;

  virtual void OnAttach() override;
  virtual void OnDetach() override;

  void OnUpdate(BEngine::Timestep ts) override;
  virtual void OnImGuiRender() override;
  void OnEvent(BEngine::Event& e) override;
private:
  BEngine::OrthographicCameraController camera_controller_;

  glm::vec4 square_color_ = { 0.2f, 0.3f, 0.8f, 1.0f };
  glm::vec3 quad_position_ = { 0.0f,0.0f,0.0f };
  glm::mat4 circle_transform_;
};