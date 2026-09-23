#include <app/MainController.hpp>

#include <engine/graphics/GraphicsController.hpp>
#include <engine/platform/PlatformController.hpp>

namespace app {
    void MainController::initialize() {
        engine::graphics::OpenGL::enable_depth_testing();

        auto resources =
                engine::core::Controller::get<engine::resources::ResourcesController>();

        auto graphics =
                engine::core::Controller::get<engine::graphics::GraphicsController>();

        m_model  = resources->model("retro_tv");
        m_shader = resources->shader("basic");

        graphics->camera()->Position = glm::vec3(0.0f, 0.0f, 3.0f);
    }

    void MainController::poll_events() {
        auto platform =
                engine::core::Controller::get<engine::platform::PlatformController>();

        constexpr float LIGHT_STEP = 0.2f;

        if (platform->key(engine::platform::KEY_J).state() ==
            engine::platform::Key::State::JustPressed) {
            m_point_position.x -= LIGHT_STEP;
        }

        if (platform->key(engine::platform::KEY_L).state() ==
            engine::platform::Key::State::JustPressed) {
            m_point_position.x += LIGHT_STEP;
        }

        if (platform->key(engine::platform::KEY_I).state() ==
            engine::platform::Key::State::JustPressed) {
            m_point_position.y += LIGHT_STEP;
        }

        if (platform->key(engine::platform::KEY_K).state() ==
            engine::platform::Key::State::JustPressed) {
            m_point_position.y -= LIGHT_STEP;
        }

        if (platform->key(engine::platform::KEY_U).state() ==
            engine::platform::Key::State::JustPressed) {
            m_point_position.z -= LIGHT_STEP;
        }

        if (platform->key(engine::platform::KEY_O).state() ==
            engine::platform::Key::State::JustPressed) {
            m_point_position.z += LIGHT_STEP;
        }

        // Point light colors
        if (platform->key(engine::platform::KEY_1).state() ==
            engine::platform::Key::State::JustPressed) {
            m_point_color = glm::vec3(1.0f, 0.0f, 0.0f);
        }

        if (platform->key(engine::platform::KEY_2).state() ==
            engine::platform::Key::State::JustPressed) {
            m_point_color = glm::vec3(0.0f, 1.0f, 0.0f);
        }

        if (platform->key(engine::platform::KEY_3).state() ==
            engine::platform::Key::State::JustPressed) {
            m_point_color = glm::vec3(0.0f, 0.0f, 1.0f);
        }

        // Directional light colors
        if (platform->key(engine::platform::KEY_4).state() ==
            engine::platform::Key::State::JustPressed) {
            m_directional_color = glm::vec3(1.0f, 0.0f, 0.0f);
        }

        if (platform->key(engine::platform::KEY_5).state() ==
            engine::platform::Key::State::JustPressed) {
            m_directional_color = glm::vec3(0.0f, 1.0f, 0.0f);
        }

        if (platform->key(engine::platform::KEY_6).state() ==
            engine::platform::Key::State::JustPressed) {
            m_directional_color = glm::vec3(0.0f, 0.0f, 1.0f);
        }
    }

    void MainController::begin_draw() {
        engine::graphics::OpenGL::clear_buffers();
    }

    void MainController::draw() {
        auto graphics =
                engine::core::Controller::get<engine::graphics::GraphicsController>();

        m_shader->use();

        glm::mat4 model = glm::mat4(1.0f);

        m_shader->set_mat4("model", model);
        m_shader->set_mat4("view", graphics->camera()->view_matrix());
        m_shader->set_mat4("projection", graphics->projection_matrix());

        m_shader->set_vec3(
            "object_color",
            glm::vec3(0.6f, 0.35f, 0.15f)
        );

        m_shader->set_vec3(
            "directional_direction",
            glm::vec3(-0.2f, -1.0f, -0.3f)
        );

        m_shader->set_vec3(
            "directional_color",
            m_directional_color
        );

        m_shader->set_vec3(
            "point_position",
            m_point_position
        );

        m_shader->set_vec3(
            "point_color",
            m_point_color
        );

        m_model->draw(m_shader);
    }

    void MainController::end_draw() {
        auto platform =
                engine::core::Controller::get<engine::platform::PlatformController>();

        platform->swap_buffers();
    }
} // namespace app
