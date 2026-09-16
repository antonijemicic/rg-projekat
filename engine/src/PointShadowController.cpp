#include <engine/graphics/PointShadowController.hpp>

#include <engine/platform/PlatformController.hpp>
#include <engine/resources/Model.hpp>
#include <engine/resources/ResourcesController.hpp>
#include <engine/resources/Shader.hpp>

#include <array>

#include <glm/gtc/matrix_transform.hpp>

namespace engine::graphics {
    void PointShadowController::initialize() {
        const auto resources =
                core::Controller::get<
                    resources::ResourcesController>();

        m_model = resources->model("room");

        m_depth_shader =
                resources->shader(
                    "point_shadow_depth");

        m_shadow =
                OpenGL::create_point_shadow_map(
                    m_shadow_size);
    }

    void PointShadowController::begin_draw() {
        const auto platform =
                core::Controller::get<
                    platform::PlatformController>();

        const glm::mat4 shadow_projection =
                glm::perspective(
                    glm::radians(90.0f),
                    1.0f,
                    m_near_plane,
                    m_far_plane);

        const std::array<glm::mat4, 6>
                shadow_matrices{
                    shadow_projection
                    * glm::lookAt(
                        m_light_position,
                        m_light_position
                        + glm::vec3(
                            1.0f,
                            0.0f,
                            0.0f),
                        glm::vec3(
                            0.0f,
                            -1.0f,
                            0.0f)),

                    shadow_projection
                    * glm::lookAt(
                        m_light_position,
                        m_light_position
                        + glm::vec3(
                            -1.0f,
                            0.0f,
                            0.0f),
                        glm::vec3(
                            0.0f,
                            -1.0f,
                            0.0f)),

                    shadow_projection
                    * glm::lookAt(
                        m_light_position,
                        m_light_position
                        + glm::vec3(
                            0.0f,
                            1.0f,
                            0.0f),
                        glm::vec3(
                            0.0f,
                            0.0f,
                            1.0f)),

                    shadow_projection
                    * glm::lookAt(
                        m_light_position,
                        m_light_position
                        + glm::vec3(
                            0.0f,
                            -1.0f,
                            0.0f),
                        glm::vec3(
                            0.0f,
                            0.0f,
                            -1.0f)),

                    shadow_projection
                    * glm::lookAt(
                        m_light_position,
                        m_light_position
                        + glm::vec3(
                            0.0f,
                            0.0f,
                            1.0f),
                        glm::vec3(
                            0.0f,
                            -1.0f,
                            0.0f)),

                    shadow_projection
                    * glm::lookAt(
                        m_light_position,
                        m_light_position
                        + glm::vec3(
                            0.0f,
                            0.0f,
                            -1.0f),
                        glm::vec3(
                            0.0f,
                            -1.0f,
                            0.0f))
                };

        OpenGL::set_viewport(
            m_shadow_size,
            m_shadow_size);

        m_depth_shader->use();

        m_depth_shader->set_vec3(
            "light_position",
            m_light_position);

        m_depth_shader->set_float(
            "far_plane",
            m_far_plane);

        m_depth_shader->set_mat4(
            "model",
            glm::mat4(1.0f));

        for (int32_t face = 0; face < 6; ++face) {
            OpenGL::bind_point_shadow_face(
                m_shadow,
                face);

            OpenGL::clear_depth_buffer();

            m_depth_shader->set_mat4(
                "shadow_matrix",
                shadow_matrices[face]);

            m_model->draw(
                m_depth_shader);
        }

        OpenGL::bind_framebuffer(0);

        OpenGL::set_viewport(
            platform->window()->width(),
            platform->window()->height());
    }

    void PointShadowController::terminate() {
        OpenGL::destroy_point_shadow_map(
            m_shadow);
    }
} // namespace engine::graphics
