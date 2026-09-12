#include <app/GUIController.hpp>
#include <app/MainController.hpp>

#include <engine/graphics/GraphicsController.hpp>

#include <imgui.h>

namespace app {
    void GUIController::initialize() {
        set_enable(false);
    }

    void GUIController::poll_events() {
        const auto platform =
                engine::core::Controller::get<engine::platform::PlatformController>();

        if (platform->key(engine::platform::KEY_F2).state()
            == engine::platform::Key::State::JustPressed) {
            set_enable(!is_enabled());
        }
    }

    void GUIController::draw() {
        auto graphics =
                engine::core::Controller::get<engine::graphics::GraphicsController>();

        auto main_controller =
                engine::core::Controller::get<MainController>();

        graphics->begin_gui();

        ImGui::Begin("Lighting");

        ImGui::Text("Point Light");

        ImGui::ColorEdit3(
            "Point Color",
            &main_controller->point_light_color().x);

        ImGui::SliderFloat3(
            "Point Position",
            &main_controller->point_light_position().x,
            -10.0f,
            10.0f);

        ImGui::Separator();

        ImGui::Text("Spot Light");

        ImGui::ColorEdit3(
            "Spot Color",
            &main_controller->spot_light_color().x);

        ImGui::Text("Spot Light follows the camera.");

        ImGui::End();

        graphics->end_gui();
    }
} // namespace app
