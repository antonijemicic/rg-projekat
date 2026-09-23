//#shader vertex
#version 330 core

layout (location = 0) in vec3 a_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(a_position, 1.0);
}

//#shader fragment
#version 330 core

out vec4 frag_color;

void main() {
    frag_color = vec4(0.6, 0.35, 0.15, 1.0);
}