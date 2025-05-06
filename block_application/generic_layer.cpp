#include "generic_layer.h"

#include "glm/gtc/type_ptr.hpp"


GenericLayer::GenericLayer() : Layer("GenericLayer") {

}

void GenericLayer::OnAttach() {
}

void GenericLayer::OnDetach() {
}

void GenericLayer::OnUpdate(BEngine::Timestep ts) {
  BEngine::Layer::OnUpdate(ts);

  //BENGINE_CORE_INFO("FPS: {}", 1 / ts);

  BEngine::RenderCommand::SetClearColor(square_color_);
  BEngine::RenderCommand::Clear();
}

void GenericLayer::OnImGuiRender() {
  ImGui::Begin("Settings");
  ImGui::ColorEdit4("Square Color", glm::value_ptr(square_color_));
  ImGui::End();
}

void GenericLayer::OnEvent(BEngine::Event &e) {
}
