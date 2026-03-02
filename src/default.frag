#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 color;

in vec3 Pos;
in vec3 Normal;

layout (location = 0) out vec4 Color;
layout (location = 1) out vec3 VoxPos;

void main() {
    vec3 pos = (view * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
    vec3 back = (view * vec4(Normal, 1.0)).xyz;
    Color = vec4(max(dot(back - pos, vec3(0.0, 0.0, 1.0)), 0.0f) * color.rgb, color.a);
    const float scale = 8.0f - 0.00001f;
    vec4 screen = projection * view * model * vec4(Pos, 1.0);
    vec4 center = projection * view * model * vec4((floor(Pos * scale) + vec3(0.5)) / scale, 1.0);
    VoxPos = vec3(0.0, 0.0, 0.5 - center.z / center.w * 0.5);
    //VoxPos = vec3(screen.xy / screen.w - center.xy / center.w, 0.5 - center.z / center.w * 0.5);
    //VoxPos = screen.xyz;
    //VoxPos = (vec4(gl_FragCoord.xy / vec2(1280.0, 720.0) * 2.0 - vec2(1.0), gl_FragCoord.z * 2.0 - 1.0, 1.0) / gl_FragCoord.w).xyz - screen.xyz;
}
