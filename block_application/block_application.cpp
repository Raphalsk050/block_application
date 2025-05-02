#include <src/block_engine.h>
#include <src/application/entry_point.h>

namespace BEngine {
  class BlockApplication : public Application {
  public:
    explicit BlockApplication(const ApplicationSpecification &spec)
      : Application(spec) {
      //PushLayer(new EditorLayer());
    }
  };

  Application *CreateApplication(ApplicationCommandLineArgs args) {
    ApplicationSpecification spec;
    spec.Name = "Block Engine";
    spec.CommandLineArgs = args;

    return new BlockApplication(spec);
  }
}
