#version 330 core

uniform mat4 view;
uniform vec4 color;

in vec3 Normal;
in vec3 Pos;

layout (location = 0) out vec4 Color;
layout (location = 1) out ivec3 VoxelPos;

void main() {
    vec3 pos = (view * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
    vec3 back = (view * vec4(Normal, 1.0)).xyz;
    Color = vec4(max(dot(back - pos, vec3(0.0, 0.0, 1.0)), 0.0f) * color.rgb, color.a);
    VoxelPos = ivec3(round(Pos * 16.0f));
}
