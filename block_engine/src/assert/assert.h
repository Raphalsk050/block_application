#pragma once
#include "../base.h"
#include "../log/belog.h"
#include <filesystem>

namespace BEngine {
#pragma once

#ifdef BENGINE_ENABLE_ASSERTS

  // Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
  // provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define BENGINE_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { BENGINE##type##ERROR(msg, __VA_ARGS__); BENGINE_DEBUGBREAK(); } }
#define BENGINE_INTERNAL_ASSERT_WITH_MSG(type, check, ...) BENGINE_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define BENGINE_INTERNAL_ASSERT_NO_MSG(type, check) BENGINE_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", BENGINE_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define BENGINE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define BENGINE_INTERNAL_ASSERT_GET_MACRO(...) BENGINE_EXPAND_MACRO( BENGINE_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, BENGINE_INTERNAL_ASSERT_WITH_MSG, BENGINE_INTERNAL_ASSERT_NO_MSG) )

  // Currently accepts at least the condition and one additional parameter (the message) being optional
#define BENGINE_ASSERT(...) BENGINE_EXPAND_MACRO( BENGINE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define BENGINE_CORE_ASSERT(...) BENGINE_EXPAND_MACRO( BENGINE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define BENGINE_ASSERT(...)
#define BENGINE_CORE_ASSERT(...)
#endif
}
