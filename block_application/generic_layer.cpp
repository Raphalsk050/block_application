#include "generic_layer.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/renderer/renderer_3d.h"

GenericLayer::GenericLayer()
    : Layer("GenericLayer"),
      camera_controller_(1280.0f / 720.0f),
      square_color_({0.2f, 0.3f, 0.8f, 1.0f}) {}

void GenericLayer::OnAttach() { BENGINE_PROFILE_FUNCTION(); }

void GenericLayer::OnDetach() { BENGINE_PROFILE_FUNCTION(); }

void GenericLayer::OnUpdate(BEngine::Timestep ts) {
  BENGINE_PROFILE_FUNCTION();

  camera_controller_.OnUpdate(ts);

  BEngine::Renderer3D::ResetStats(); // Alterado para Renderer3D
  {
    BENGINE_PROFILE_SCOPE("Renderer Prep");
    BEngine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    BEngine::RenderCommand::Clear();
  }

  {
    static float rotation = 0.0f;
    rotation += ts * 1.0f;
    circle_transform_ = glm::translate(glm::mat4(1.0f), glm::vec3(sin(rotation), cos(rotation), 0.0f));
    BENGINE_PROFILE_SCOPE("Renderer Draw");
    BEngine::Renderer3D::BeginScene(camera_controller_.GetCamera());
    BEngine::Renderer3D::DrawBox(quad_position_, quad_size_, square_color_);
    BEngine::Renderer3D::DrawBox({1.0f,2.0f,2.0f}, {10.0,10.0,10.0}, {0.0,1.0,0.0,1.0});
    BEngine::Renderer3D::DrawBox({3.0f,4.0f,2.0f}, quad_size_, {1.0,1.0,1.0,1.0});
    BEngine::Renderer3D::DrawLine3D(quad_position_, {1.0, 1.0, 1.0}, {1.0,0.0,0.0,1.0});
    BEngine::Renderer3D::EndScene();
  }
}

void GenericLayer::OnImGuiRender() {
  BENGINE_PROFILE_FUNCTION();

  ImGui::Begin("Settings");
  ImGui::SliderFloat3("Quad position", glm::value_ptr(quad_position_), -1.0f, 1.0f, "%.3f");
  ImGui::SliderFloat3("Quad size", glm::value_ptr(quad_size_), -1.0f, 1.0f, "%.3f");
  ImGui::End();
}

void GenericLayer::OnEvent(BEngine::Event& e) { camera_controller_.OnEvent(e); }