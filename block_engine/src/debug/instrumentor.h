#pragma once

#define BENGINE_PROFILE 0
#if BENGINE_PROFILE
// Resolve which function signature macro will be used. Note that this only
// is resolved when the (pre)compiler starts, so the syntax highlighting
// could mark the wrong one in your editor!
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || \
    (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#define BENGINE_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define BENGINE_FUNC_SIG __PRETTY_FUNCTION__
#elif (defined(__FUNCSIG__) || (_MSC_VER))
#define BENGINE_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || \
    (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define BENGINE_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define BENGINE_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define BENGINE_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define BENGINE_FUNC_SIG __func__
#else
#define BENGINE_FUNC_SIG "BENGINE_FUNC_SIG unknown!"
#endif

#define BENGINE_PROFILE_BEGIN_SESSION(name, filepath) \
  ::BEngine::Instrumentor::Get().BeginSession(name, filepath)
#define BENGINE_PROFILE_END_SESSION() \
  ::BEngine::Instrumentor::Get().EndSession()
#define BENGINE_PROFILE_SCOPE_LINE2(name, line)                            \
  constexpr auto fixedName##line =                                         \
      ::BEngine::InstrumentorUtils::CleanupOutputString(name, "__cdecl "); \
  ::BEngine::InstrumentationTimer timer##line(fixedName##line.Data)
#define BENGINE_PROFILE_SCOPE_LINE(name, line) \
  BENGINE_PROFILE_SCOPE_LINE2(name, line)
#define BENGINE_PROFILE_SCOPE(name) BENGINE_PROFILE_SCOPE_LINE(name, __LINE__)
#define BENGINE_PROFILE_FUNCTION() BENGINE_PROFILE_SCOPE(BENGINE_FUNC_SIG)
#else
#define BENGINE_PROFILE_BEGIN_SESSION(name, filepath)
#define BENGINE_PROFILE_END_SESSION()
#define BENGINE_PROFILE_SCOPE(name)
#define BENGINE_PROFILE_FUNCTION()
#endif