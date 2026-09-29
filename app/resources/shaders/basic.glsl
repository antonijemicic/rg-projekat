//#shader vertex
#version 330 core

layout(location=0) in vec3 a_position;

layout(location=1) in vec3 a_normal;

layout(location=2) in vec2 a_tex_coords;

out vec3 frag_position;
out vec3 frag_normal;

out vec2 frag_tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    frag_position=vec3(model*vec4(a_position, 1.0));
    frag_normal=mat3(transpose(inverse(model)))*a_normal;
    frag_tex_coords=a_tex_coords;
    gl_Position=projection*view*model*vec4(a_position, 1.0);
}

//#shader fragment
#version 330 core

struct DirectionalLight{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 frag_tex_coords;
in vec3 frag_position;
in vec3 frag_normal;

out vec4 frag_color;

uniform sampler2D texture_diffuse1;
uniform DirectionalLight directional_light;
uniform PointLight point_light;

uniform vec3 view_position;
uniform vec3 material_specular;
uniform float material_shininess;

vec3 calculate_directional_light(
        DirectionalLight light,
        vec3 normal,
        vec3 view_direction,
        vec3 color
) {
    vec3 directional_direction=normalize(-light.direction);

    float directional_diffuse_strength=max(dot(normal, directional_direction), 0.0);
    vec3 directional_reflection=reflect(-directional_direction, normal);
    float directional_specular_strength=pow(max(dot(view_direction, directional_reflection), 0.0), material_shininess);

    vec3 directional_ambient=light.ambient*color;
    vec3 directional_diffuse=light.diffuse*directional_diffuse_strength*color;
    vec3 directional_specular=light.specular*directional_specular_strength*material_specular;

    return directional_ambient+directional_diffuse+directional_specular;

}

vec3 calculate_point_light(
        PointLight light,
        vec3 normal,
        vec3 fragment_position,
        vec3 view_direction,
        vec3 color
) {
    vec3 point_direction=normalize(light.position-fragment_position);

    float point_diffuse_strength=max(dot(normal, point_direction), 0.0);
    vec3 point_reflection=reflect(-point_direction, normal);
    float point_specular_strength=pow(max(dot(view_direction, point_reflection), 0.0), material_shininess);

    float distance=length(light.position-fragment_position);
    float attenuation=1.0/(1.0+0.09*distance+0.032*distance*distance);

    vec3 point_ambient=light.ambient*color;
    vec3 point_diffuse=light.diffuse*point_diffuse_strength*color;
    vec3 point_specular=light.specular*point_specular_strength*material_specular;

    point_ambient=point_ambient*attenuation;
    point_diffuse=point_diffuse*attenuation;
    point_specular=point_specular*attenuation;

    return point_ambient + point_diffuse + point_specular;
}

void main(){
    vec3 color=texture(texture_diffuse1, frag_tex_coords).rgb;
    vec3 normal=normalize(frag_normal);
    vec3 view_direction=normalize(view_position-frag_position);

    vec3 directional_result=calculate_directional_light(
        directional_light,
        normal,
        view_direction,
        color
    );

    vec3 point_result=calculate_point_light(
        point_light,
        normal,
        frag_position,
        view_direction,
        color
    );

    vec3 result=directional_result+point_result;

    frag_color=vec4(result, 1.0);
}