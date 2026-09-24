#pragma once

#include <engine/core/Engine.hpp>

namespace app {
    class MainController final : public engine::core::Controller {
    protected:
        void initialize() override;

        void poll_events() override;

        void update() override;

        void begin_draw() override;

        void draw() override;

        void end_draw() override;

    private:
        struct DirectionalLight {
            glm::vec3 direction{-0.2f, -1.0f, -0.3f};

            glm::vec3 ambient{0.2f, 0.2f, 0.2f};
            glm::vec3 diffuse{0.8f, 0.8f, 0.8f};
            glm::vec3 specular{1.0f, 1.0f, 1.0f};
        };

        struct PointLight {
            glm::vec3 position{1.5f, 1.0f, 2.0f};

            glm::vec3 ambient{0.1f, 0.07f, 0.04f};
            glm::vec3 diffuse{1.0f, 0.7f, 0.4f};
            glm::vec3 specular{1.0f, 0.7f, 0.4f};
        };

        engine::resources::Model *m_model{};
        engine::resources::Shader *m_shader{};

        DirectionalLight m_directional_light{};
        PointLight m_point_light{};

        bool m_timed_light_sequence_active{false};

        bool m_point_light_red_event_done{false};
        bool m_point_light_moved_and_directional_blue_event_done{false};

        float m_light_sequence_start_time{0.0f};
    };
} // namespace app
