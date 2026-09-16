// clang-format off
#include <glad/glad.h>
// clang-format on

#include <engine/graphics/OpenGL.hpp>
#include <engine/util/Errors.hpp>

namespace engine::graphics {
    OpenGL::FramebufferData OpenGL::create_framebuffer(
        int32_t width,
        int32_t height) {
        FramebufferData framebuffer_data{};

        CHECKED_GL_CALL(
            glGenFramebuffers,
            1,
            &framebuffer_data.framebuffer);

        CHECKED_GL_CALL(
            glBindFramebuffer,
            GL_FRAMEBUFFER,
            framebuffer_data.framebuffer);

        CHECKED_GL_CALL(
            glGenTextures,
            1,
            &framebuffer_data.color_texture);

        CHECKED_GL_CALL(
            glBindTexture,
            GL_TEXTURE_2D,
            framebuffer_data.color_texture);

        CHECKED_GL_CALL(
            glTexImage2D,
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            width,
            height,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            nullptr);

        CHECKED_GL_CALL(
            glTexParameteri,
            GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            GL_LINEAR);

        CHECKED_GL_CALL(
            glTexParameteri,
            GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER,
            GL_LINEAR);

        CHECKED_GL_CALL(
            glFramebufferTexture2D,
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D,
            framebuffer_data.color_texture,
            0);

        CHECKED_GL_CALL(
            glGenRenderbuffers,
            1,
            &framebuffer_data.renderbuffer);

        CHECKED_GL_CALL(
            glBindRenderbuffer,
            GL_RENDERBUFFER,
            framebuffer_data.renderbuffer);

        CHECKED_GL_CALL(
            glRenderbufferStorage,
            GL_RENDERBUFFER,
            GL_DEPTH24_STENCIL8,
            width,
            height);

        CHECKED_GL_CALL(
            glFramebufferRenderbuffer,
            GL_FRAMEBUFFER,
            GL_DEPTH_STENCIL_ATTACHMENT,
            GL_RENDERBUFFER,
            framebuffer_data.renderbuffer);

        const auto status =
                CHECKED_GL_CALL(
                    glCheckFramebufferStatus,
                    GL_FRAMEBUFFER);

        RG_GUARANTEE(
            status == GL_FRAMEBUFFER_COMPLETE,
            "Post-processing framebuffer is incomplete.");

        CHECKED_GL_CALL(
            glBindTexture,
            GL_TEXTURE_2D,
            0);

        CHECKED_GL_CALL(
            glBindRenderbuffer,
            GL_RENDERBUFFER,
            0);

        CHECKED_GL_CALL(
            glBindFramebuffer,
            GL_FRAMEBUFFER,
            0);

        return framebuffer_data;
    }

    void OpenGL::bind_framebuffer(
        uint32_t framebuffer) {
        CHECKED_GL_CALL(
            glBindFramebuffer,
            GL_FRAMEBUFFER,
            framebuffer);
    }

    void OpenGL::destroy_framebuffer(
        const FramebufferData &framebuffer) {
        CHECKED_GL_CALL(
            glDeleteRenderbuffers,
            1,
            &framebuffer.renderbuffer);

        CHECKED_GL_CALL(
            glDeleteTextures,
            1,
            &framebuffer.color_texture);

        CHECKED_GL_CALL(
            glDeleteFramebuffers,
            1,
            &framebuffer.framebuffer);
    }

    OpenGL::ScreenQuadData OpenGL::create_screen_quad() {
        ScreenQuadData screen_quad{};

        const float vertices[] = {
            -1.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,

            -1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f
        };

        CHECKED_GL_CALL(
            glGenVertexArrays,
            1,
            &screen_quad.vao);

        CHECKED_GL_CALL(
            glGenBuffers,
            1,
            &screen_quad.vbo);

        CHECKED_GL_CALL(
            glBindVertexArray,
            screen_quad.vao);

        CHECKED_GL_CALL(
            glBindBuffer,
            GL_ARRAY_BUFFER,
            screen_quad.vbo);

        CHECKED_GL_CALL(
            glBufferData,
            GL_ARRAY_BUFFER,
            sizeof(vertices),
            vertices,
            GL_STATIC_DRAW);

        CHECKED_GL_CALL(
            glEnableVertexAttribArray,
            0);

        CHECKED_GL_CALL(
            glVertexAttribPointer,
            0,
            2,
            GL_FLOAT,
            GL_FALSE,
            4 * sizeof(float),
            reinterpret_cast<void *>(0));

        CHECKED_GL_CALL(
            glEnableVertexAttribArray,
            1);

        CHECKED_GL_CALL(
            glVertexAttribPointer,
            1,
            2,
            GL_FLOAT,
            GL_FALSE,
            4 * sizeof(float),
            reinterpret_cast<void *>(
                2 * sizeof(float)));

        CHECKED_GL_CALL(
            glBindVertexArray,
            0);

        return screen_quad;
    }

    void OpenGL::draw_screen_quad(
        const ScreenQuadData &screen_quad,
        uint32_t texture_id) {
        CHECKED_GL_CALL(
            glActiveTexture,
            GL_TEXTURE0);

        CHECKED_GL_CALL(
            glBindTexture,
            GL_TEXTURE_2D,
            texture_id);

        CHECKED_GL_CALL(
            glBindVertexArray,
            screen_quad.vao);

        CHECKED_GL_CALL(
            glDrawArrays,
            GL_TRIANGLES,
            0,
            6);

        CHECKED_GL_CALL(
            glBindVertexArray,
            0);
    }

    void OpenGL::destroy_screen_quad(
        const ScreenQuadData &screen_quad) {
        CHECKED_GL_CALL(
            glDeleteVertexArrays,
            1,
            &screen_quad.vao);

        CHECKED_GL_CALL(
            glDeleteBuffers,
            1,
            &screen_quad.vbo);
    }
} // namespace engine::graphics
