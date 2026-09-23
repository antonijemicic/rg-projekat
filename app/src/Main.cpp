#include <engine/core/Engine.hpp>

#include <app/MainController.hpp>

namespace app {
    class MainApp final : public engine::core::App {
    private:
        void app_setup() override {
            auto main_controller = register_controller<MainController>();

            main_controller->after(
                engine::core::Controller::get<engine::core::EngineControllersEnd>()
            );
        }
    };
} // namespace app

int main(int argc, char **argv) {
    app::MainApp application;

    return application.run(argc, argv);
}
