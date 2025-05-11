#include "block_engine/src/camera/camera_3d_controller.h"
#include "block_engine/bepch.h"

#include "block_engine/src/input/input.h"
#include "block_engine/src/input/key_codes.h"
#include "block_engine/src/input/mouse_codes.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace BEngine {

Camera3DController::Camera3DController(float aspectRatio, ControlMode mode)
    : m_AspectRatio(aspectRatio), m_ControlMode(mode)
{
    m_Camera = Camera3D(45.0f, aspectRatio, 0.1f, 1000.0f);
    
    // Default camera position and orientation
    m_Camera.SetPosition({0.0f, 2.0f, 5.0f});
    m_Camera.SetRotation({glm::radians(-15.0f), 0.0f, 0.0f}); // Look slightly down
}

void Camera3DController::OnUpdate(Timestep ts)
{
    BENGINE_PROFILE_FUNCTION();

    m_Forward = Input::IsKeyPressed(Key::W);
    m_Backward = Input::IsKeyPressed(Key::S);
    m_Left = Input::IsKeyPressed(Key::A);
    m_Right = Input::IsKeyPressed(Key::D);
    m_Up = Input::IsKeyPressed(Key::E);
    m_Down = Input::IsKeyPressed(Key::Q);
    
    // Update based on control mode
    switch (m_ControlMode)
    {
        case ControlMode::Fly:
            UpdateFlyMode(ts);
            break;
        case ControlMode::Orbit:
            UpdateOrbitMode(ts);
            break;
        case ControlMode::FirstPerson:
            UpdateFirstPersonMode(ts);
            break;
    }
}

void Camera3DController::UpdateFlyMode(Timestep ts)
{
    // Get current camera orientation vectors
    glm::vec3 forward = m_Camera.GetForwardDirection();
    glm::vec3 right = m_Camera.GetRightDirection();
    glm::vec3 up = m_Camera.GetUpDirection();
    
    // Current position
    glm::vec3 position = m_Camera.GetPosition();
    float velocity = m_MovementSpeed * ts;
    
    // Check input state (from OnKeyPressed events)
    if (m_Forward)
        position += forward * velocity;
    if (m_Backward)
        position -= forward * velocity;
    if (m_Right)
        position += right * velocity;
    if (m_Left)
        position -= right * velocity;
    if (m_Up)
        position += up * velocity;
    if (m_Down)
        position -= up * velocity;
    
    // Update camera position
    m_Camera.SetPosition(position);
}

void Camera3DController::UpdateOrbitMode(Timestep ts)
{
    // In orbit mode, we rotate around a focal point
    UpdateCameraPositionFromOrbit();
}

void Camera3DController::UpdateFirstPersonMode(Timestep ts)
{
    // Similar to fly mode but with restricted pitch and no roll
    glm::vec3 forward = m_Camera.GetForwardDirection();
    glm::vec3 right = m_Camera.GetRightDirection();
    
    // Remove vertical component for forward movement (stays at same height)
    forward.y = 0.0f;
    forward = glm::normalize(forward);
    
    // Current position
    glm::vec3 position = m_Camera.GetPosition();
    float velocity = m_MovementSpeed * ts;
    
    // Check input state
    if (m_Forward)
        position += forward * velocity;
    if (m_Backward)
        position -= forward * velocity;
    if (m_Right)
        position += right * velocity;
    if (m_Left)
        position -= right * velocity;
    if (m_Up)
        position.y += velocity;
    if (m_Down)
        position.y -= velocity;
    
    // Update camera position
    m_Camera.SetPosition(position);
}

void Camera3DController::UpdateCameraPositionFromOrbit()
{
    // Calculate position based on orbit distance and angles
    float pitch = glm::radians(m_Pitch);
    float yaw = glm::radians(m_Yaw);
    
    // Convert spherical coordinates to cartesian
    float x = m_Distance * std::cos(pitch) * std::sin(yaw);
    float y = m_Distance * std::sin(pitch);
    float z = m_Distance * std::cos(pitch) * std::cos(yaw);
    
    // Position is relative to focal point
    glm::vec3 focalPoint = m_Camera.GetFocalPoint();
    glm::vec3 position = focalPoint + glm::vec3(x, y, z);
    
    // Point camera at focal point
    glm::vec3 direction = glm::normalize(focalPoint - position);
    float pitchAngle = glm::asin(direction.y);
    float yawAngle = glm::atan(direction.x, direction.z);
    
    // Set camera position and rotation
    m_Camera.SetPosition(position);
    m_Camera.SetRotation({pitchAngle, yawAngle, 0.0f});
}

void Camera3DController::OnEvent(Event& e)
{
    BENGINE_PROFILE_FUNCTION();
    
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseMovedEvent>(BENGINE_BIND_EVENT_FN(Camera3DController::OnMouseMoved));
    dispatcher.Dispatch<MouseScrolledEvent>(BENGINE_BIND_EVENT_FN(Camera3DController::OnMouseScrolled));
    dispatcher.Dispatch<WindowResizeEvent>(BENGINE_BIND_EVENT_FN(Camera3DController::OnWindowResized));
    dispatcher.Dispatch<KeyPressedEvent>(BENGINE_BIND_EVENT_FN(Camera3DController::OnKeyPressed));
}

bool Camera3DController::OnMouseMoved(MouseMovedEvent& e)
{
    if (!m_MouseControlEnabled)
        return false;
    
    if (m_FirstMouse)
    {
        m_LastMousePosition = {e.GetX(), e.GetY()};
        m_FirstMouse = false;
        return false;
    }

    // Calcular delta do mouse
    float xOffset = m_LastMousePosition.x - e.GetX();
    float yOffset = m_LastMousePosition.y - e.GetY();
    m_LastMousePosition = {e.GetX(), e.GetY()};

    xOffset *= m_RotationSpeed;
    yOffset *= m_RotationSpeed;

    if (m_ControlMode == ControlMode::Orbit)
    {
        m_Yaw += xOffset;
        m_Pitch = glm::clamp(m_Pitch + yOffset, -89.0f, 89.0f);

        UpdateCameraPositionFromOrbit();
    }
    else
    {

        glm::vec3 currentRotation = m_Camera.GetRotation();

        glm::quat orientation = glm::quat(glm::vec3(currentRotation.x, currentRotation.y, currentRotation.z));

        glm::vec3 right = m_Camera.GetRightDirection();
        glm::vec3 up = m_Camera.GetUpDirection();

        glm::quat pitchQuat = glm::angleAxis(glm::radians(yOffset), right);
        glm::quat yawQuat = glm::angleAxis(glm::radians(xOffset), up);

        orientation = yawQuat * pitchQuat * orientation;
        orientation = glm::normalize(orientation);

        glm::vec3 eulerAngles = glm::eulerAngles(orientation);

        float pitchDegrees = glm::degrees(eulerAngles.x);
        if (pitchDegrees > 89.0f) pitchDegrees = 89.0f;
        if (pitchDegrees < -89.0f) pitchDegrees = -89.0f;
        eulerAngles.x = glm::radians(pitchDegrees);

        if (m_ControlMode == ControlMode::FirstPerson)
            eulerAngles.z = 0.0f;

        m_Camera.SetRotation(eulerAngles);
    }
    
    return false;
}

bool Camera3DController::OnMouseScrolled(MouseScrolledEvent& e)
{
    float zoomAmount = e.GetYOffset() * m_ZoomSpeed;
    
    if (m_ControlMode == ControlMode::Orbit)
    {
        // In orbit mode, adjust the distance
        m_Distance = std::max(1.0f, m_Distance - zoomAmount);
        UpdateCameraPositionFromOrbit();
    }
    else
    {
        // In other modes, zoom changes the movement speed
        m_MovementSpeed = std::max(1.0f, m_MovementSpeed + zoomAmount);
    }
    
    return false;
}

bool Camera3DController::OnWindowResized(WindowResizeEvent& e)
{
    OnResize(static_cast<float>(e.GetWidth()), static_cast<float>(e.GetHeight()));
    return false;
}

bool Camera3DController::OnKeyPressed(KeyPressedEvent& e)
{
    bool pressed = (e.IsRepeat() || !e.IsRepeat()); // Include repeats or not
    //BENGINE_CORE_INFO("Key {} state is: {}",e.GetKeyCode(),pressed);
    // Update movement state based on keys
    switch (e.GetKeyCode())
    {
        case Key::Space:
            m_MouseControlEnabled = !m_MouseControlEnabled;
            m_FirstMouse = true;
            break;
    }
    
    return false;
}

void Camera3DController::OnResize(float width, float height)
{
    m_AspectRatio = width / height;
    m_Camera.SetViewport(width, height);
}

void Camera3DController::SetPosition(const glm::vec3& position)
{
    m_Camera.SetPosition(position);
}

void Camera3DController::SetRotation(const glm::vec3& rotation)
{
    // Convert from degrees to radians for internal representation
    glm::vec3 radians = glm::vec3(
        glm::radians(rotation.x),
        glm::radians(rotation.y),
        glm::radians(rotation.z)
    );
    
    m_Camera.SetRotation(radians);
    
    // Update derived pitch and yaw for orbit mode
    m_Pitch = rotation.x;
    m_Yaw = rotation.y;
    m_Roll = rotation.z;
}

void Camera3DController::SetFocalPoint(const glm::vec3& focalPoint)
{
    m_Camera.SetFocalPoint(focalPoint);
    
    if (m_ControlMode == ControlMode::Orbit)
    {
        // Update camera position to maintain orbit around new focal point
        UpdateCameraPositionFromOrbit();
    }
}

} // namespace BEngine