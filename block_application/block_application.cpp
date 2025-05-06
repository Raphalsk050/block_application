#include <src/application/entry_point.h>
#include <src/block_engine.h>
#include <src/layer/layer.h>

#include "generic_layer.h"

class BlockApplication : public BEngine::Application {
public:
  BlockApplication(const BEngine::ApplicationSpecification &spec)
    : BEngine::Application(spec) {
    PushLayer(new GenericLayer());
  }
};

BEngine::Application *BEngine::CreateApplication(BEngine::ApplicationCommandLineArgs args) {
  BEngine::ApplicationSpecification spec;
  spec.Name = "Block Engine";
  spec.Width = 800;
  spec.Height = 600;
  spec.CommandLineArgs = args;


  return new BlockApplication(spec);
}
