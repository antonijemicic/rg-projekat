#ifndef MATF_RG_PROJECT_MAINCONTROLLER_HPP
#define MATF_RG_PROJECT_MAINCONTROLLER_HPP

#include <engine/core/Engine.hpp>

namespace app {
    class MainController final : public engine::core::Controller {
    public:
        std::string_view name() const override {
            return "app::MainController";
        }

    private:
        void initialize() override;

        bool loop() override;

        void poll_events() override;

        void update() override;

        void begin_draw() override;

        void draw() override;

        void end_draw() override;

        void draw_room();

        void update_camera();

        glm::vec3 m_point_light_position{0.0f, 3.0f, 2.0f};
        glm::vec3 m_point_light_color{1.0f, 1.0f, 1.0f};

        glm::vec3 m_spot_light_color{1.0f, 1.0f, 1.0f};
    };
} // namespace app

#endif // MATF_RG_PROJECT_MAINCONTROLLER_HPP
