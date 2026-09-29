#include <engine/core/Engine.hpp>
#include <app/MainController.hpp>

namespace app {
    class MainApp final : public engine::core::App {
    protected:
        void app_setup() override {
            auto main_controller = register_controller<MainController>();

            main_controller->after(
                engine::core::Controller::get<engine::core::EngineControllersEnd>()
            );
        }
    };
}

int main(int argc, char **argv) {
    return std::make_unique<app::MainApp>()->run(argc, argv);
}
