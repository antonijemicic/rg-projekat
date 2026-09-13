#ifndef MATF_RG_PROJECT_POINTSHADOWCONTROLLER_HPP
#define MATF_RG_PROJECT_POINTSHADOWCONTROLLER_HPP

#include <engine/core/Controller.hpp>
#include <engine/graphics/OpenGL.hpp>

#include <glm/glm.hpp>

namespace engine::resources {
    class Model;
    class Shader;
}

namespace engine::graphics {
    class PointShadowController final : public core::Controller {
    public:
        std::string_view name() const override {
            return "PointShadowController";
        }

        void set_light_position(
            const glm::vec3 &light_position) {
            m_light_position = light_position;
        }

        uint32_t depth_cubemap() const {
            return m_shadow.depth_cubemap;
        }

        float far_plane() const {
            return m_far_plane;
        }

    private:
        void initialize() override;

        void begin_draw() override;

        void terminate() override;

        resources::Model *m_model{nullptr};
        resources::Shader *m_depth_shader{nullptr};

        OpenGL::PointShadowData m_shadow{};

        glm::vec3 m_light_position{
            0.0f,
            1.5f,
            0.0f
        };

        int32_t m_shadow_size{1024};

        float m_near_plane{0.1f};
        float m_far_plane{100.0f};
    };
} // namespace engine::graphics

#endif // MATF_RG_PROJECT_POINTSHADOWCONTROLLER_HPP
