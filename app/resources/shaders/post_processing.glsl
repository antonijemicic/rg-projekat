//#shader vertex
#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main() {
    TexCoords = aTexCoords;

    gl_Position =
    vec4(aPos.x, aPos.y, 0.0, 1.0);
}

//#shader fragment
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screen_texture;
uniform int effect;

void main() {
    vec4 color =
    texture(screen_texture, TexCoords);

    if (effect == 1) {
        FragColor =
        vec4(
        vec3(1.0) - color.rgb,
        1.0);

        return;
    }

    if (effect == 2) {
        float gray =
        0.2126 * color.r
        + 0.7152 * color.g
        + 0.0722 * color.b;

        FragColor =
        vec4(
        vec3(gray),
        1.0);

        return;
    }

    FragColor = color;
}