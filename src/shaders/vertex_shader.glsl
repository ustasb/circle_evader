#version 410 core

layout (location = 0) in vec4 window_vpos;
layout (location = 1) in vec4 vcolor;
layout (location = 2) in int window_size;

out vec4 vs_color;

void main(void) {
  vec4 normalized_vpos = vec4(
    (window_vpos[0] - window_size) / window_size,
    (window_vpos[1] + window_size) / window_size,
    window_vpos[2],
    1.0
  );

  gl_Position = normalized_vpos;
  vs_color = vcolor;
}
