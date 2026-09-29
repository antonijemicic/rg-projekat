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
        enum class ColorPreset {
            Red,
            Green,
            Blue
        };

        struct DirectionalLight {
            glm::vec3 direction{-0.2f, -1.0f, -0.3f};
            glm::vec3 ambient{0.4f, 0.4f, 0.4f};
            glm::vec3 diffuse{0.8f, 0.8f, 0.8f};
            glm::vec3 specular{1.0f, 1.0f, 1.0f};

            void set(ColorPreset color) {
                glm::vec3 value{};

                switch (color) {
                    case ColorPreset::Red:
                        value=glm::vec3{1.0f, 0.0f, 0.0f};
                        break;

                    case ColorPreset::Green:
                        value=glm::vec3{0.0f, 1.0f, 0.0f};
                        break;

                    case ColorPreset::Blue:
                        value=glm::vec3{0.0f, 0.0f, 1.0f};
                        break;
                }

                ambient=0.2f*value;
                diffuse=value;
                specular=value;
            }

            void reset() {
                direction=glm::vec3{-0.2f, -1.0f, -0.3f};
                ambient=glm::vec3{0.4f, 0.4f, 0.4f};
                diffuse=glm::vec3{0.8f, 0.8f, 0.8f};
                specular=glm::vec3{1.0f, 1.0f, 1.0f};
            }
        };

        struct PointLight {
            glm::vec3 position{1.5f, 1.0f, 2.0f};
            glm::vec3 ambient{0.1f, 0.07f, 0.04f};
            glm::vec3 diffuse{1.0f, 0.7f, 0.4f};
            glm::vec3 specular{1.0f, 0.7f, 0.4f};

            void set(ColorPreset color) {
                glm::vec3 value{};

                switch (color) {
                    case ColorPreset::Red:
                        value=glm::vec3{1.0f, 0.0f, 0.0f};
                        break;

                    case ColorPreset::Green:
                        value=glm::vec3{0.0f, 1.0f, 0.0f};
                        break;

                    case ColorPreset::Blue:
                        value=glm::vec3{0.0f, 0.0f, 1.0f};
                        break;
                }

                ambient=0.2f*value;
                diffuse=value;
                specular=value;
            }

            void reset() {
                position=glm::vec3{1.5f, 1.0f, 2.0f};
                ambient=glm::vec3{0.1f, 0.07f, 0.04f};
                diffuse=glm::vec3{1.0f, 0.7f, 0.4f};
                specular=glm::vec3{1.0f, 0.7f, 0.4f};
            }
        };

        engine::resources::Model *m_model{};
        engine::resources::Shader *m_shader{};

        DirectionalLight m_directional_light{};
        PointLight m_point_light{};

        enum class EventState {
            Idle,
            WaitingForPointRed,
            WaitingForPointMoveAndDirectionalBlue
        };

        EventState m_event_state{EventState::Idle};

        float m_event_state_start_time{0.0f};
    };
}
