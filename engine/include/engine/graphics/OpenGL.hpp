#ifndef OPENGL_HPP
#define OPENGL_HPP

#include <cstdint>
#include <engine/resources/Shader.hpp>
#include <filesystem>

namespace engine::resources {
    class Skybox;
}

#define CHECKED_GL_CALL(func, ...) \
    engine::graphics::OpenGL::call( \
            std::source_location::current(), \
            func __VA_OPT__(, ) __VA_ARGS__)

namespace engine::graphics {
    class OpenGL {
    public:
        using ShaderProgramId = uint32_t;

        struct FramebufferData {
            uint32_t framebuffer{0};
            uint32_t color_texture{0};
            uint32_t renderbuffer{0};
        };

        struct ScreenQuadData {
            uint32_t vao{0};
            uint32_t vbo{0};
        };

        template<typename TResult, typename... TOpenGLArgs, typename... Args>
        static TResult call(
            std::source_location location,
            TResult (*glfun)(TOpenGLArgs...),
            Args &&... args) {
        // @formatter:off
        if constexpr (!std::is_same_v<TResult, void>) {
            auto result = glfun(std::forward<Args>(args)...);

#ifndef NDEBUG
            assert_no_error(location);
#endif

            return result;
        } else {
            glfun(std::forward<Args>(args)...);

#ifndef NDEBUG
            assert_no_error(location);
#endif
        }
            // @formatter:on
        }

        static int32_t shader_type_to_opengl_type(
            resources::ShaderType type);

        static uint32_t generate_texture(
            const std::filesystem::path &path,
            bool flip_uvs);

        static int32_t texture_format(
            int32_t number_of_channels);

        static uint32_t init_skybox_cube();

        static bool shader_compiled_successfully(
            uint32_t shader_id);

        static uint32_t compile_shader(
            const std::string &shader_source,
            resources::ShaderType shader_type);

        static uint32_t load_skybox_textures(
            const std::filesystem::path &path,
            bool flip_uvs = false);

        static void enable_depth_testing();

        static void disable_depth_testing();

        static void clear_buffers();

        static std::string get_compilation_error_message(
            uint32_t shader_id);

        static FramebufferData create_framebuffer(
            int32_t width,
            int32_t height);

        static void bind_framebuffer(
            uint32_t framebuffer);

        static void destroy_framebuffer(
            const FramebufferData &framebuffer);

        static ScreenQuadData create_screen_quad();

        static void draw_screen_quad(
            const ScreenQuadData &screen_quad,
            uint32_t texture_id);

        static void destroy_screen_quad(
            const ScreenQuadData &screen_quad);

    private:
        static void assert_no_error(
            std::source_location location);
    };
} // namespace engine::graphics

#endif // OPENGL_HPP
