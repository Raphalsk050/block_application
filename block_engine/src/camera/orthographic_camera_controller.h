#pragma once

#include "block_engine/src/camera/orthographic_camera.h"
#include "block_engine/src/timestep.h"

#include "block_engine/src/event/window_application_event.h"
#include "block_engine/src/event/mouse_event.h"

namespace BEngine {

class OrthographicCameraController
{
public:
  OrthographicCameraController(float aspectRatio, bool rotation = false);

  void OnUpdate(Timestep ts);
  void OnEvent(Event& e);

  void OnResize(float width, float height);

  OrthographicCamera& GetCamera() { return camera_; }
  const OrthographicCamera& GetCamera() const { return camera_; }

  float GetZoomLevel() const { return zoom_level_; }
  void SetZoomLevel(float level) { zoom_level_ = level; }
private:
  bool OnMouseScrolled(MouseScrolledEvent& e);
  bool OnWindowResized(WindowResizeEvent& e);
private:
  float aspect_ratio_ = 1.0f;
  float zoom_level_ = 1.0f;
  OrthographicCamera camera_;

  bool rotation_;

  glm::vec3 camera_position_ = { 0.0f, 0.0f, 0.0f };
  float camera_rotation_ = 0.0f; //In degrees, in the anti-clockwise direction
  float camera_translation_speed_ = 5.0f;
  float camera_rotation_speed_ = 180.0f;
};

}