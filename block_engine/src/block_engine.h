#pragma once

#include "types.h"
#include "window/generic_glfw_window.h"
#include "window/window.h"
#include "input/input.h"
#include "input/key_codes.h"
#include "input/mouse_codes.h"
#include "application/application.h"
#include "assert/assert.h"
#include "debug/instrumentor.h"
#include "log/belog.h"
#include <imgui.h>
#include <glm/glm.hpp>

#include "renderer/renderer.h"
#include "renderer/renderer_2d.h"
#include "renderer/buffer.h"
#include "renderer/graphics_context.h"
#include "renderer/render_command.h"
#include "renderer/renderer_api.h"
#include "renderer/vertex_array.h"
#include "renderer/texture.h"

#include "camera/orthographic_camera.h"
#include "camera/orthographic_camera_controller.h"



