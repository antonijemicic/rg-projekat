#include <app/GUIController.hpp>
#include <app/MainApp.hpp>
#include <app/MainController.hpp>

#include <engine/graphics/PostProcessingController.hpp>

namespace app {
    void MainApp::app_setup() {
        auto main_controller =
                register_controller<MainController>();

        auto post_processing_controller =
                register_controller<
                    engine::graphics::
                    PostProcessingController>();

        auto gui_controller =
                register_controller<GUIController>();

        main_controller->after(
            engine::core::Controller::get<
                engine::core::
                EngineControllersEnd>());

        post_processing_controller->after(
            main_controller);

        gui_controller->after(
            post_processing_controller);
    }
} // namespace app
