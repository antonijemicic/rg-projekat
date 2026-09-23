//#shader vertex
#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 frag_position;
out vec3 normal;

void main() {
    vec4 world_position = model * vec4(a_position, 1.0);

    frag_position = world_position.xyz;
    normal = mat3(transpose(inverse(model))) * a_normal;

    gl_Position = projection * view * world_position;
}

//#shader fragment
#version 330 core

in vec3 frag_position;
in vec3 normal;

out vec4 frag_color;

uniform vec3 object_color;

uniform vec3 directional_direction;
uniform vec3 directional_color;

uniform vec3 point_position;
uniform vec3 point_color;

void main() {
    vec3 n = normalize(normal);

    // Directional light
    vec3 dir_to_light = normalize(-directional_direction);

    float directional_diffuse =
    max(dot(n, dir_to_light), 0.0);

    vec3 directional =
    0.20 * directional_color +
    directional_diffuse * directional_color;

    // Point light
    vec3 point_to_light =
    normalize(point_position - frag_position);

    float point_diffuse =
    max(dot(n, point_to_light), 0.0);

    float distance_to_light =
    length(point_position - frag_position);

    float attenuation =
    1.0 /
    (1.0 +
    0.09 * distance_to_light +
    0.032 * distance_to_light * distance_to_light);

    vec3 point =
    (0.10 * point_color +
    point_diffuse * point_color) *
    attenuation;

    vec3 result =
    (directional + point) * object_color;

    frag_color = vec4(result, 1.0);
}