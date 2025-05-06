#pragma once
#include "assert.h"
#include "application.h"

// #ifdef BENGINE_PLATFORM_WINDOWS
//
// extern BEngine::Application *BEngine::CreateApplication(ApplicationCommandLineArgs args);
//
// inline int main(int argc, char **argv) {
//   BEngine::Belog::Init();
//
//   BENGINE_PROFILE_BEGIN_SESSION("Startup", "BlockEngineProfile-Startup.json");
//   auto app = BEngine::CreateApplication({argc, argv});
//   BENGINE_PROFILE_END_SESSION();
//
//   BENGINE_PROFILE_BEGIN_SESSION("Runtime", "BlockEngineProfile-Runtime.json");
//   app->Run();
//   BENGINE_PROFILE_END_SESSION();
//
//   BENGINE_PROFILE_BEGIN_SESSION("Shutdown", "BlockEngineProfile-Shutdown.json");
//   delete app;
//   BENGINE_PROFILE_END_SESSION();
// }
//
// #elif defined(BENGINE_PLATFORM_APPLE) || defined(BENGINE_PLATFORM_LINUX)
//
// #endif


extern BEngine::Application *BEngine::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char **argv) {
  BEngine::Belog::Init();

  BENGINE_PROFILE_BEGIN_SESSION("Startup", "Profile-Startup.json");
  auto app = BEngine::CreateApplication({argc, argv});
  BENGINE_PROFILE_END_SESSION();

  BENGINE_PROFILE_BEGIN_SESSION("Runtime", "Profile-Runtime.json");
  app->Run();
  BENGINE_PROFILE_END_SESSION();

  BENGINE_PROFILE_BEGIN_SESSION("Shutdown", "Profile-Shutdown.json");
  delete app;
  BENGINE_PROFILE_END_SESSION();
  return 0;
}
