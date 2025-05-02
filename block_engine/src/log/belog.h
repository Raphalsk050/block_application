#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace BEngine {
  class Belog {
  public:
    // Initialize the Logger (call once at startup)
    static void Init(const std::string &engineName = "BENGINE");

    // Retrieve the core logger
    inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }

    // (Optional) Retrieve a client/user logger
    inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }

  private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
  };
}

#ifdef DEBUG

#define BENGINE_CORE_TRACE(...)    ::BEngine::Belog::GetCoreLogger()->trace(__VA_ARGS__)
#define BENGINE_CORE_INFO(...)     ::BEngine::Belog::GetCoreLogger()->info(__VA_ARGS__)
#define BENGINE_CORE_WARN(...)     ::BEngine::Belog::GetCoreLogger()->warn(__VA_ARGS__)
#define BENGINE_CORE_ERROR(...)    ::BEngine::Belog::GetCoreLogger()->error(__VA_ARGS__)
#define BENGINE_CORE_CRITICAL(...) ::BEngine::Belog::GetCoreLogger()->critical(__VA_ARGS__)

#else

#define BENGINE_CORE_TRACE(...)    do {} while(false)
#define BENGINE_CORE_INFO(...)     do {} while(false)
#define BENGINE_CORE_WARN(...)     do {} while(false)
#define BENGINE_CORE_ERROR(...)    do {} while(false)
#define BENGINE_CORE_CRITICAL(...) do {} while(false)

#endif
