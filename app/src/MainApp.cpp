#include <app/GUIController.hpp>
#include <app/MainApp.hpp>
#include <app/MainController.hpp>

namespace app {
    void MainApp::app_setup() {
        auto main_controller = register_controller<MainController>();
        auto gui_controller  = register_controller<GUIController>();

        main_controller->after(
            engine::core::Controller::get<engine::core::EngineControllersEnd>());

        gui_controller->after(main_controller);
    }
} // namespace app
