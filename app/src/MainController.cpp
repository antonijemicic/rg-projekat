#include <app/MainController.hpp>

#include <engine/graphics/GraphicsController.hpp>

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

    void MainController::draw() {
        auto graphics =
                engine::core::Controller::get<engine::graphics::GraphicsController>();

        m_shader->use();

        glm::mat4 model = glm::mat4(1.0f);

        m_shader->set_mat4("model", model);
        m_shader->set_mat4("view", graphics->camera()->view_matrix());
        m_shader->set_mat4("projection", graphics->projection_matrix());

        m_model->draw(m_shader);
    }
} // namespace app
