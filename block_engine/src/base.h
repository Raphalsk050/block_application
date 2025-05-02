#pragma once
#include <memory>


#ifdef DEBUG
#if defined(BENGINE_PLATFORM_WINDOWS)
    #define BENGINE_DEBUGBREAK() __debugbreak()
#elif defined(BENGINE_PLATFORM_LINUX)
    #include <signal.h>
    #define BENGINE_DEBUGBREAK() raise(SIGTRAP)
#elif defined(BENGINE_PLATFORM_APPLE)
#include <signal.h>
#define BENGINE_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define BENGINE_ENABLE_ASSERTS

#else
#define BENGINE_DEBUGBREAK()
#endif

#define BENGINE_EXPAND_MACRO(x) x
#define BENGINE_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define BENGINE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace BEngine {
  template<typename T>
  using Scope = std::unique_ptr<T>;

  template<typename T, typename... Args>
  constexpr Scope<T> CreateScope(Args &&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
  }

  template<typename T>
  using Ref = std::shared_ptr<T>;

  template<typename T, typename... Args>
  constexpr Ref<T> CreateRef(Args &&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }
}

#include "log/belog.h"
#include "assert/assert.h"
