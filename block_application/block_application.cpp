#include <src/application/entry_point.h>
#include <src/block_engine.h>
#include <src/layer/layer.h>

namespace BEngine {
class BlockApplication : public Application {
 public:
  explicit BlockApplication(const ApplicationSpecification &spec)
      : Application(spec) {
    // PushLayer(new EditorLayer());
  }
};

Application *CreateApplication(ApplicationCommandLineArgs args) {
  ApplicationSpecification spec;
  spec.Name = "Block Engine";
  spec.Width = 800;
  spec.Height = 600;
  spec.CommandLineArgs = args;

  return new BlockApplication(spec);
}
}  // namespace BEngine
