#include "generic_layer.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GenericLayer::GenericLayer()
    : Layer("GenericLayer"),
      camera_controller_(1280.0f / 720.0f),
      square_color_({0.2f, 0.3f, 0.8f, 1.0f}) {}

void GenericLayer::OnAttach() { BENGINE_PROFILE_FUNCTION(); }

void GenericLayer::OnDetach() { BENGINE_PROFILE_FUNCTION(); }

void GenericLayer::OnUpdate(BEngine::Timestep ts) {
  BENGINE_PROFILE_FUNCTION();

  // Update
  camera_controller_.OnUpdate(ts);

  BEngine::Renderer2D::ResetStats();
  {
    BENGINE_PROFILE_SCOPE("Renderer Prep");
    BEngine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    BEngine::RenderCommand::Clear();
  }

  {
    BENGINE_PROFILE_SCOPE("Renderer Draw");
    BEngine::Renderer2D::BeginScene(camera_controller_.GetCamera());
    BEngine::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f},
                                  {1.0f, 0.2f, 0.3f, 1.0f});
    BEngine::Renderer2D::EndScene();
  }
}

void GenericLayer::OnImGuiRender() {
  BENGINE_PROFILE_FUNCTION();
  camera_position_ = camera_controller_.GetCamera().GetPosition();

  ImGui::Begin("Settings");

  auto stats = BEngine::Renderer2D::GetStats();
  ImGui::Text("Renderer2D Stats:");
  ImGui::Text("Draw Calls: %d", stats.DrawCalls);
  ImGui::Text("Quads: %d", stats.QuadCount);
  ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
  ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
  ImGui::Text("Camera position: (%f,%f,%f)", camera_position_.x,camera_position_.y,camera_position_.z);

  ImGui::End();
}

void GenericLayer::OnEvent(BEngine::Event& e) { camera_controller_.OnEvent(e); }