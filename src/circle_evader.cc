#include <iostream>
#include <glm/glm.hpp>
#include "circle_evader.h"
#include "gl_helpers.h"

CircleEvader::CircleEvader(const int circle_cnt, const int window_size)
  : circle_cnt_{circle_cnt}, window_size_{window_size} {}

void CircleEvader::print_instructions() {
  std::cout << "\n=========================\n"
    << "Welcome to Circle Evader!\n"
    << "=========================\n\n"
    << "Evade the circles with your mouse. The game ends if you fail!\n"
    << "The longer you last, the higher your score.\n" << std::endl;
}

void CircleEvader::startup() {
  print_instructions();

  create_circles();

  rendering_program_ = compile_shaders();
  glGenVertexArrays(1, &vertex_array_obj_);
  glBindVertexArray(vertex_array_obj_);
}

void CircleEvader::update(const double time, const double mousex, const double mousey) {
  if (!game_over_) {
    score_ = time;
  }

  for (auto& circle: circles_) {
    circle.update(time, window_size_);

    if (circle.is_point_inside(mousex, mousey)) {
      game_over_ = true;
    }
  }
}

void CircleEvader::render(const double time) {
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

  const GLfloat bg_color[] = {
    static_cast<GLfloat>(glm::sin(time)),
    static_cast<GLfloat>(glm::cos(time)),
    0.0f, 1.0f};
  glClearBufferfv(GL_COLOR, 0, bg_color);

  glUseProgram(rendering_program_);

  glVertexAttribI1i(2, window_size_);

  GLuint vertex_buffer_obj;
  glGenBuffers(1, &vertex_buffer_obj);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_obj);

  // Yes, this is ugly.
  GLfloat vertexData[5000];
  int size = 0;

  for (auto& c : circles_) {
    size += c.add_vertices_to_buffer(vertexData, size);
  }

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

  int vertex_cnt = size / 3;
  int vertex_cnt_per_circle = vertex_cnt / circle_cnt_;

  GLfloat color[] = { 1.0f, 0.0f, 0.0f, 0.0f }; // red
  for (int i = 0; i < circle_cnt_; ++i) {
    // Draw the circle
    color[1] = 0.0f;
    glVertexAttrib4fv(1, color);
    glDrawArrays(GL_TRIANGLE_FAN, vertex_cnt_per_circle * i, vertex_cnt_per_circle);

    // Draw the border
    color[1] = 1.0f;
    glVertexAttrib4fv(1, color);
    glDrawArrays(GL_TRIANGLE_STRIP, vertex_cnt_per_circle * i, vertex_cnt_per_circle);
  }
}

GLuint CircleEvader::compile_shaders() {
  GLuint vertex_shader = load_shader_from_file("src/shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
  GLuint fragment_shader = load_shader_from_file("src/shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);
  GLuint program = glCreateProgram();

  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return program;
}

void CircleEvader::print_exit_msg() {
  std::cout << "\nThanks for playing!\nYour score was: " << score_ << std::endl;
}

void CircleEvader::shutdown() {
  glDeleteVertexArrays(1, &vertex_array_obj_);
  glDeleteProgram(rendering_program_);

  print_exit_msg();
}

void CircleEvader::create_circles() {
  for (int i = 0; i < circle_cnt_; ++i) {
    double x = rand() % window_size_;
    double y = rand() % window_size_;
    double radius = 10 + rand() % 50;
    double vx = 0.2 + rand() % 4;
    double vy = 0.2 + rand() % 4;

    Circle circle {x, y, radius, vx, vy};
    circles_.push_back(circle);
  }
}
