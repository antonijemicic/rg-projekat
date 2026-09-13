#include <app/GUIController.hpp>
#include <app/MainController.hpp>

#include <engine/graphics/GraphicsController.hpp>
#include <engine/graphics/PointShadowController.hpp>
#include <engine/graphics/PostProcessingController.hpp>

#include <imgui.h>

namespace app {
    void GUIController::initialize() {
        set_enable(false);
    }

    void GUIController::poll_events() {
        const auto platform =
                engine::core::Controller::get<
                    engine::platform::
                    PlatformController>();

        if (platform
            ->key(engine::platform::KEY_F2)
            .state()
            == engine::platform::Key::State::
            JustPressed) {
            set_enable(!is_enabled());
        }
    }

    void GUIController::draw() {
        auto graphics =
                engine::core::Controller::get<
                    engine::graphics::
                    GraphicsController>();

        auto main_controller =
                engine::core::Controller::get<
                    MainController>();

        auto post_processing =
                engine::core::Controller::get<
                    engine::graphics::
                    PostProcessingController>();

        auto point_shadows =
                engine::core::Controller::get<
                    engine::graphics::
                    PointShadowController>();

        graphics->begin_gui();

        ImGui::Begin("Lighting");

        ImGui::Text("Point Light");

        ImGui::ColorEdit3(
            "Point Color",
            &main_controller
             ->point_light_color()
             .x);

        ImGui::SliderFloat3(
            "Point Position",
            &main_controller
             ->point_light_position()
             .x,
            -10.0f,
            10.0f);

        ImGui::Separator();

        ImGui::Text("Spot Light");

        ImGui::ColorEdit3(
            "Spot Color",
            &main_controller
             ->spot_light_color()
             .x);

        ImGui::Text(
            "Spot Light follows the camera.");

        ImGui::Separator();

        bool shadows_enabled =
                point_shadows->is_enabled();

        if (ImGui::Checkbox(
            "Point Shadows",
            &shadows_enabled)) {
            point_shadows->set_enable(
                shadows_enabled);
        }

        ImGui::Separator();

        ImGui::Text("Post-processing");

        int effect =
                static_cast<int>(
                    post_processing->effect());

        const char *effects[] = {
            "None",
            "Invert",
            "Grayscale"
        };

        if (ImGui::Combo(
            "Effect",
            &effect,
            effects,
            3)) {
            post_processing->set_effect(
                static_cast<
                    engine::graphics::
                    PostProcessingEffect>(
                    effect));
        }

        ImGui::End();

        graphics->end_gui();
    }
} // namespace app
