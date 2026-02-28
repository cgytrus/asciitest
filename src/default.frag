#version 330 core

uniform mat4 view;

in vec3 normal;

out vec4 color;

void main() {
    vec3 pos = (view * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
    vec3 back = (view * vec4(normal, 1.0)).xyz;
    color = vec4(max(dot(back - pos, vec3(0.0, 0.0, 1.0)), 0.0f) * vec3(1.0f, 0.5f, 0.2f), 1.0f);
}
