#pragma once

#include "block_engine/src/block_engine.h"
#include "src/camera/camera_3d_controller.h"

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
  BEngine::Camera3DController camera_controller_;

  glm::vec4 square_color_ = { 1.0,1.0,1.0, 1.0f };
  glm::vec3 quad_position_ = { 0.0f,0.0f,0.0f };
  glm::vec3 quad_size_ = { 0.0f,0.0f,0.0f };
  glm::mat4 circle_transform_;
};