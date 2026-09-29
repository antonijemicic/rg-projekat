#include <app/MainController.hpp>
#include <engine/graphics/GraphicsController.hpp>

namespace app {
    void MainController::initialize() {
        engine::graphics::OpenGL::enable_depth_testing();

        auto resources=engine::core::Controller::get<engine::resources::ResourcesController>();

        m_model=resources->model("armchair");
        m_shader=resources->shader("basic");

        auto graphics=engine::core::Controller::get<engine::graphics::GraphicsController>();
        graphics->camera()->Position=glm::vec3(0.0f,0.0f,5.0f);
    }

    void MainController::poll_events() {
        auto platform=engine::core::Controller::get<engine::platform::PlatformController>();

        if (platform->key(engine::platform::KeyId::KEY_J).state()==engine::platform::Key::State::Pressed) {
            m_point_light.position.x=m_point_light.position.x-0.02f;
        }

        if (platform->key(engine::platform::KeyId::KEY_L).state()==engine::platform::Key::State::Pressed) {
            m_point_light.position.x=m_point_light.position.x+0.02f;
        }

        if (platform->key(engine::platform::KeyId::KEY_I).state()==engine::platform::Key::State::Pressed) {
            m_point_light.position.y=m_point_light.position.y+0.02f;
        }

        if (platform->key(engine::platform::KeyId::KEY_K).state()==engine::platform::Key::State::Pressed) {
            m_point_light.position.y=m_point_light.position.y-0.02f;
        }

        if (platform->key(engine::platform::KeyId::KEY_U).state()==engine::platform::Key::State::Pressed) {
            m_point_light.position.z=m_point_light.position.z-0.02f;
        }

        if (platform->key(engine::platform::KeyId::KEY_O).state()==engine::platform::Key::State::Pressed) {
            m_point_light.position.z=m_point_light.position.z+0.02f;
        }

        if (platform->key(engine::platform::KeyId::KEY_1).state()==engine::platform::Key::State::JustPressed) {
            m_point_light.set(ColorPreset::Red);
        }

        if (platform->key(engine::platform::KeyId::KEY_2).state()==engine::platform::Key::State::JustPressed) {
            m_point_light.set(ColorPreset::Green);
        }

        if (platform->key(engine::platform::KeyId::KEY_3).state()==engine::platform::Key::State::JustPressed) {
            m_point_light.set(ColorPreset::Blue);
        }

        if (platform->key(engine::platform::KeyId::KEY_4).state()==engine::platform::Key::State::JustPressed) {
            m_directional_light.set(ColorPreset::Red);
        }

        if (platform->key(engine::platform::KeyId::KEY_5).state()==engine::platform::Key::State::JustPressed) {
            m_directional_light.set(ColorPreset::Green);
        }

        if (platform->key(engine::platform::KeyId::KEY_6).state()==engine::platform::Key::State::JustPressed) {
            m_directional_light.set(ColorPreset::Blue);
        }

        if (platform->key(engine::platform::KeyId::KEY_E).state()==engine::platform::Key::State::JustPressed) {
            m_point_light.reset();
            m_directional_light.reset();

            m_event_state=EventState::WaitingForPointRed;
            m_event_state_start_time=platform->frame_time().current;
        }
    }

    void MainController::update() {

        auto platform=engine::core::Controller::get<engine::platform::PlatformController>();

        float current_time=platform->frame_time().current;
        float elapsed=current_time-m_event_state_start_time;

        switch (m_event_state) {
            case EventState::Idle:
                break;

            case EventState::WaitingForPointRed:
              if (elapsed>=2.0f) {
                  m_point_light.set(ColorPreset::Red);

                  m_event_state=EventState::WaitingForPointMoveAndDirectionalBlue;
                  m_event_state_start_time=current_time;
            }
                break;

            case EventState::WaitingForPointMoveAndDirectionalBlue:
            if (elapsed>=3.0f) {
                  m_point_light.position=glm::vec3(-1.5f, 1.0f, 2.0f);

                  m_directional_light.set(ColorPreset::Blue);

                m_event_state=EventState::Idle;
            }
                break;
        }
    }

    void MainController::begin_draw() {
        engine::graphics::OpenGL::clear_buffers();
    }

    void MainController::draw() {
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();

        glm::mat4 model=glm::mat4(1.0f);
        model=glm::translate(model, glm::vec3(0.2f, 0.2f, 0.0f));
        model=glm::scale(model, glm::vec3(0.002f));
        model=glm::rotate(model, glm::radians(-60.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        m_shader->use();
        m_shader->set_mat4("model", model);
        m_shader->set_mat4("view", graphics->camera()->view_matrix());
        m_shader->set_mat4("projection", graphics->projection_matrix());

        m_shader->set_vec3("view_position", graphics->camera()->Position);

        m_shader->set_vec3("directional_light.direction", m_directional_light.direction);
        m_shader->set_vec3("directional_light.ambient", m_directional_light.ambient);
        m_shader->set_vec3("directional_light.diffuse", m_directional_light.diffuse);
        m_shader->set_vec3("directional_light.specular", m_directional_light.specular);

        m_shader->set_vec3("point_light.position", m_point_light.position);
        m_shader->set_vec3("point_light.ambient", m_point_light.ambient);
        m_shader->set_vec3("point_light.diffuse", m_point_light.diffuse);
        m_shader->set_vec3("point_light.specular", m_point_light.specular);

        m_shader->set_vec3("material_specular", glm::vec3(0.5f));
        m_shader->set_float("material_shininess", 32.0f);

        m_model->draw(m_shader);
    }

    void MainController::end_draw() {
        auto platform=engine::core::Controller::get<engine::platform::PlatformController>();

        platform->swap_buffers();
    }
}
