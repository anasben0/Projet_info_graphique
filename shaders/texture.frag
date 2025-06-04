#version 330 core

in vec2 frag_tex_coords;
uniform sampler2D diffuse_map;

out vec4 FragColor;

void main() {
    FragColor = texture(diffuse_map, frag_tex_coords);
}