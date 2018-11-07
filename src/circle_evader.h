#ifndef CIRCLE_EVADER_H
#define CIRCLE_EVADER_H

#include <GL/glew.h>
#include <vector>
#include "circle.h"

class CircleEvader {
 public:
  CircleEvader(const int circle_cnt, const int window_size);

  void startup();
  void print_instructions();

  void update(const double time, const double mousex, const double mousey);
  void render(const double time);
  bool is_game_over() { return game_over_; }

  void print_exit_msg();
  void shutdown();

 private:
  GLuint compile_shaders();
  void create_circles();

  GLuint rendering_program_;
  GLuint vertex_array_obj_;
  std::vector<Circle> circles_;
  const int circle_cnt_;
  const int window_size_;
  int score_ = 0;
  bool game_over_ = false;
};

#endif
