#include <app/GUIController.hpp>
#include <app/MainController.hpp>

#include <engine/graphics/GraphicsController.hpp>

namespace app {
    void MainController::initialize() {
        engine::graphics::OpenGL::enable_depth_testing();

        auto camera =
                engine::core::Controller::get<engine::graphics::GraphicsController>()
                ->camera();

        camera->Position = glm::vec3(0.0f, 2.0f, 8.0f);
    }

    bool MainController::loop() {
        const auto platform =
                engine::core::Controller::get<engine::platform::PlatformController>();

        if (platform->key(engine::platform::KeyId::KEY_ESCAPE).state()
            == engine::platform::Key::State::JustPressed) {
            return false;
        }

        return true;
    }

    void MainController::poll_events() {
        const auto platform =
                engine::core::Controller::get<engine::platform::PlatformController>();

        if (platform->key(engine::platform::KEY_E).state()
            == engine::platform::Key::State::JustPressed) {
            start_event_sequence();
        }
    }

    void MainController::update() {
        update_camera();
        update_event_sequence();
    }

    void MainController::begin_draw() {
        engine::graphics::OpenGL::clear_buffers();
    }

    void MainController::draw() {
        draw_room();
    }

    void MainController::end_draw() {
        engine::core::Controller::get<engine::platform::PlatformController>()
                ->swap_buffers();
    }

    void MainController::draw_room() {
        auto graphics =
                engine::core::Controller::get<engine::graphics::GraphicsController>();

        auto resources =
                engine::core::Controller::get<engine::resources::ResourcesController>();

        auto shader = resources->shader("room");
        auto room   = resources->model("room");

        shader->use();

        shader->set_mat4(
            "projection",
            graphics->projection_matrix());

        shader->set_mat4(
            "view",
            graphics->camera()->view_matrix());

        shader->set_mat4(
            "model",
            glm::mat4(1.0f));

        shader->set_vec3(
            "point_light_position",
            m_point_light_position);

        shader->set_vec3(
            "point_light_color",
            m_point_light_color);

        auto camera = graphics->camera();

        shader->set_vec3(
            "spot_light_position",
            camera->Position);

        shader->set_vec3(
            "spot_light_direction",
            camera->Front);

        shader->set_vec3(
            "spot_light_color",
            m_spot_light_color);

        shader->set_vec3(
            "object_color",
            glm::vec3(0.8f, 0.7f, 0.6f));

        room->draw(shader);
    }

    void MainController::update_camera() {
        auto gui = engine::core::Controller::get<GUIController>();

        if (gui->is_enabled()) {
            return;
        }

        auto platform =
                engine::core::Controller::get<engine::platform::PlatformController>();

        auto camera =
                engine::core::Controller::get<engine::graphics::GraphicsController>()
                ->camera();

        const float dt = platform->dt();

        if (platform->key(engine::platform::KEY_W).state()
            == engine::platform::Key::State::Pressed) {
            camera->move_camera(
                engine::graphics::Camera::Movement::FORWARD,
                dt);
        }

        if (platform->key(engine::platform::KEY_S).state()
            == engine::platform::Key::State::Pressed) {
            camera->move_camera(
                engine::graphics::Camera::Movement::BACKWARD,
                dt);
        }

        if (platform->key(engine::platform::KEY_A).state()
            == engine::platform::Key::State::Pressed) {
            camera->move_camera(
                engine::graphics::Camera::Movement::LEFT,
                dt);
        }

        if (platform->key(engine::platform::KEY_D).state()
            == engine::platform::Key::State::Pressed) {
            camera->move_camera(
                engine::graphics::Camera::Movement::RIGHT,
                dt);
        }

        if (platform->key(engine::platform::KEY_LEFT).state()
            == engine::platform::Key::State::Pressed) {
            camera->rotate_camera(-1.5f, 0.0f);
        }

        if (platform->key(engine::platform::KEY_RIGHT).state()
            == engine::platform::Key::State::Pressed) {
            camera->rotate_camera(1.5f, 0.0f);
        }

        if (platform->key(engine::platform::KEY_UP).state()
            == engine::platform::Key::State::Pressed) {
            camera->rotate_camera(0.0f, 1.5f);
        }

        if (platform->key(engine::platform::KEY_DOWN).state()
            == engine::platform::Key::State::Pressed) {
            camera->rotate_camera(0.0f, -1.5f);
        }

        const auto mouse = platform->mouse();

        camera->rotate_camera(mouse.dx, mouse.dy);
        camera->zoom(mouse.scroll);
    }

    void MainController::start_event_sequence() {
        m_event_timer           = 0.0f;
        m_event_sequence_active = true;
        m_event_a_triggered     = false;

        m_point_light_position = glm::vec3(0.0f, 3.0f, 2.0f);
        m_point_light_color    = glm::vec3(1.0f);
        m_spot_light_color     = glm::vec3(1.0f);
    }

    void MainController::update_event_sequence() {
        if (!m_event_sequence_active) {
            return;
        }

        const auto platform =
                engine::core::Controller::get<engine::platform::PlatformController>();

        m_event_timer += platform->dt();

        if (m_event_timer >= 2.0f && !m_event_a_triggered) {
            m_point_light_color = glm::vec3(1.0f, 0.0f, 0.0f);

            m_event_a_triggered = true;
        }

        if (m_event_timer >= 5.0f) {
            m_point_light_position = glm::vec3(-3.0f, 1.0f, 0.0f);
            m_spot_light_color     = glm::vec3(0.0f, 0.2f, 1.0f);

            m_event_sequence_active = false;
        }
    }
} // namespace app
