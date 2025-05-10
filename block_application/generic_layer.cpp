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

  camera_controller_.OnUpdate(ts);

  BEngine::Renderer2D::ResetStats();
  {
    BENGINE_PROFILE_SCOPE("Renderer Prep");
    BEngine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    BEngine::RenderCommand::Clear();
  }

  {
    static float rotation = 0.0f;
    rotation += ts * 50.0f;

    BENGINE_PROFILE_SCOPE("Renderer Draw");
    BEngine::Renderer2D::BeginScene(camera_controller_.GetCamera());
    BEngine::Renderer2D::DrawQuad({0.0,0.0,0.0}, {1.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f});
    BEngine::Renderer2D::DrawRotatedQuad(quad_position_, { 1.0f, 1.0f }, rotation,{1.0f,1.0f,1.0f,1.0f});
    BEngine::Renderer2D::EndScene();
  }
}

void GenericLayer::OnImGuiRender() {
  BENGINE_PROFILE_FUNCTION();

  ImGui::Begin("Settings");
  ImGui::SliderFloat3("Quad position", glm::value_ptr(quad_position_), -1.0f, 1.0f, "%.3f");
  ImGui::End();
}

void GenericLayer::OnEvent(BEngine::Event& e) { camera_controller_.OnEvent(e); }