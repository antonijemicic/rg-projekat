//#shader vertex
#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_tex_coords;

out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vec4 world_position = model * vec4(a_position, 1.0);
    frag_position = world_position.xyz;

    frag_normal = mat3(transpose(inverse(model))) * a_normal;
    frag_tex_coords = a_tex_coords;

    gl_Position = projection * view * world_position;
}

//#shader fragment
#version 330 core

in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_tex_coords;

out vec4 frag_color;

uniform vec3 view_position;

uniform vec3 directional_direction;
uniform vec3 directional_color;

uniform vec3 point_position;
uniform vec3 point_color;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main() {
    vec3 norm = normalize(frag_normal);
    vec3 view_dir = normalize(view_position - frag_position);

    vec3 albedo = texture(texture_diffuse1, frag_tex_coords).rgb;
    vec3 specular_map = texture(texture_specular1, frag_tex_coords).rgb;

    // ===== Directional light =====
    vec3 dir_light_dir = normalize(-directional_direction);

    float dir_diff = max(dot(norm, dir_light_dir), 0.0);
    vec3 dir_reflect_dir = reflect(-dir_light_dir, norm);
    float dir_spec = pow(max(dot(view_dir, dir_reflect_dir), 0.0), 32.0);

    vec3 dir_ambient = 0.2 * directional_color * albedo;
    vec3 dir_diffuse = dir_diff * directional_color * albedo;
    vec3 dir_specular = dir_spec * directional_color * specular_map;

    // ===== Point light =====
    vec3 point_light_dir = normalize(point_position - frag_position);

    float point_diff = max(dot(norm, point_light_dir), 0.0);
    vec3 point_reflect_dir = reflect(-point_light_dir, norm);
    float point_spec = pow(max(dot(view_dir, point_reflect_dir), 0.0), 32.0);

    float distance_to_light = length(point_position - frag_position);
    float attenuation = 1.0 / (1.0 + 0.09 * distance_to_light + 0.032 * distance_to_light * distance_to_light);

    vec3 point_ambient = 0.1 * point_color * albedo;
    vec3 point_diffuse = point_diff * point_color * albedo;
    vec3 point_specular = point_spec * point_color * specular_map;

    point_ambient *= attenuation;
    point_diffuse *= attenuation;
    point_specular *= attenuation;

    vec3 result =
    dir_ambient + dir_diffuse + dir_specular +
    point_ambient + point_diffuse + point_specular;

    frag_color = vec4(result, 1.0);
}