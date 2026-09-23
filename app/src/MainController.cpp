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

        m_model  = resources->model("backpack");
        m_shader = resources->shader("basic");

        graphics->camera()->Position = glm::vec3(0.0f, 0.0f, 7.0f);
    }

    void MainController::poll_events() {
        auto platform =
                engine::core::Controller::get<engine::platform::PlatformController>();

        constexpr float light_step = 0.2f;

        if (platform->key(engine::platform::KEY_J).state() ==
            engine::platform::Key::State::JustPressed) {
            m_point_position.x -= light_step;
        }

        if (platform->key(engine::platform::KEY_L).state() ==
            engine::platform::Key::State::JustPressed) {
            m_point_position.x += light_step;
        }

        if (platform->key(engine::platform::KEY_I).state() ==
            engine::platform::Key::State::JustPressed) {
            m_point_position.y += light_step;
        }

        if (platform->key(engine::platform::KEY_K).state() ==
            engine::platform::Key::State::JustPressed) {
            m_point_position.y -= light_step;
        }

        if (platform->key(engine::platform::KEY_U).state() ==
            engine::platform::Key::State::JustPressed) {
            m_point_position.z -= light_step;
        }

        if (platform->key(engine::platform::KEY_O).state() ==
            engine::platform::Key::State::JustPressed) {
            m_point_position.z += light_step;
        }

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

        if (platform->key(engine::platform::KEY_E).state() ==
            engine::platform::Key::State::JustPressed) {
            m_event_sequence_active = true;
            m_event_a_done          = false;
            m_event_b_done          = false;

            m_event_start_time = platform->frame_time().current;

            m_point_position    = glm::vec3(1.5f, 1.0f, 2.0f);
            m_point_color       = glm::vec3(1.0f, 0.7f, 0.4f);
            m_directional_color = glm::vec3(1.0f, 1.0f, 1.0f);
        }
    }

    void MainController::update() {
        if (!m_event_sequence_active) {
            return;
        }

        auto platform =
                engine::core::Controller::get<engine::platform::PlatformController>();

        float elapsed_seconds =
                platform->frame_time().current - m_event_start_time;

        if (!m_event_a_done && elapsed_seconds >= 2.0f) {
            m_point_color = glm::vec3(1.0f, 0.0f, 0.0f);

            m_event_a_done = true;
        }

        if (m_event_a_done &&
            !m_event_b_done &&
            elapsed_seconds >= 5.0f) {
            m_point_position    = glm::vec3(-1.5f, 1.0f, 2.0f);
            m_directional_color = glm::vec3(0.0f, 0.0f, 1.0f);

            m_event_b_done          = true;
            m_event_sequence_active = false;
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
            "view_position",
            graphics->camera()->Position
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
