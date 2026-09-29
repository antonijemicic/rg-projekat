#include <app/MainController.hpp>

namespace app {
    void MainController::initialize() {
        engine::graphics::OpenGL::enable_depth_testing();
    }
}
