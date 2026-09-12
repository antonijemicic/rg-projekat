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

        if (platform->key(engine::platform::KEY_F1).state()
            == engine::platform::Key::State::JustPressed) {
            m_cursor_enabled = !m_cursor_enabled;
            platform->set_enable_cursor(m_cursor_enabled);
        }
    }

    void MainController::update() {
        update_camera();
    }

    void MainController::begin_draw() {
        engine::graphics::OpenGL::clear_buffers();
    }

    void MainController::end_draw() {
        engine::core::Controller::get<engine::platform::PlatformController>()
                ->swap_buffers();
    }

    void MainController::update_camera() {
        auto platform =
                engine::core::Controller::get<engine::platform::PlatformController>();

        auto camera =
                engine::core::Controller::get<engine::graphics::GraphicsController>()
                ->camera();

        const float dt = platform->dt();

        if (platform->key(engine::platform::KEY_W).state()
            == engine::platform::Key::State::Pressed) {
            camera->move_camera(engine::graphics::Camera::Movement::FORWARD, dt);
        }

        if (platform->key(engine::platform::KEY_S).state()
            == engine::platform::Key::State::Pressed) {
            camera->move_camera(engine::graphics::Camera::Movement::BACKWARD, dt);
        }

        if (platform->key(engine::platform::KEY_A).state()
            == engine::platform::Key::State::Pressed) {
            camera->move_camera(engine::graphics::Camera::Movement::LEFT, dt);
        }

        if (platform->key(engine::platform::KEY_D).state()
            == engine::platform::Key::State::Pressed) {
            camera->move_camera(engine::graphics::Camera::Movement::RIGHT, dt);
        }

        const auto mouse = platform->mouse();

        camera->rotate_camera(mouse.dx, mouse.dy);
        camera->zoom(mouse.scroll);
    }

    void MainController::draw() {
        draw_room();
    }

    void MainController::draw_room() {
        auto graphics =
                engine::core::Controller::get<engine::graphics::GraphicsController>();

        auto resources =
                engine::core::Controller::get<engine::resources::ResourcesController>();

        auto shader = resources->shader("room");
        auto room   = resources->model("room");

        shader->use();

        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());
        shader->set_mat4("model", glm::mat4(1.0f));

        shader->set_vec3("light_direction", glm::vec3(-0.5f, -1.0f, -0.3f));
        shader->set_vec3("light_color", glm::vec3(1.0f));
        shader->set_vec3("object_color", glm::vec3(0.8f, 0.7f, 0.6f));

        room->draw(shader);
    }
} // namespace app
