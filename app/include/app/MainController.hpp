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
        engine::resources::Model *m_model{};
        engine::resources::Shader *m_shader{};

        glm::vec3 m_point_position{1.5f, 1.0f, 2.0f};

        glm::vec3 m_point_color{1.0f, 0.7f, 0.4f};
        glm::vec3 m_directional_color{1.0f, 1.0f, 1.0f};

        bool m_event_sequence_active{false};
        bool m_event_a_done{false};
        bool m_event_b_done{false};

        float m_event_start_time{0.0f};
    };
} // namespace app
