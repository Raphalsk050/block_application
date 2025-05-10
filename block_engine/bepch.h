#pragma once
#define BENGINE_PROFILE 1

#ifdef BENGINE_PLATFORM_WINDOWS
/*#ifndef NOMINMAX
    // See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
    #define NOMINMAX
#endif*/
#endif

#include <algorithm>
#include <array>
#include <functional>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "src/base.h"
#include "src/debug/instrumentor.h"
#include "src/log/belog.h"

// #ifdef BENGINE_PLATFORM_WINDOWS
//   #include <Windows.h>
// #endif
