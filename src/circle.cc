#include <glm/glm.hpp>
#include "circle.h"

const int RETINA_SCALE = 2;
const int VERT_ELEMENT_CNT = 32 * 3; // 32 triangles with x,y,z
const double PI = 3.14159265f;
const double SLICE = 2 * PI / VERT_ELEMENT_CNT;

namespace {
  const int MIN_RADIUS = 10;
  const int MAX_RADIUS = 70;
}

Circle::Circle(double x, double y, double radius, double vx, double vy)
  : x_{x}, y_{y}, radius_{radius}, vx_{vx}, vy_{vy} {}

void Circle::update(const double time, const int window_size) {
  x_ += vx_;
  y_ += vy_;

  double new_radius = glm::abs(radius_ + glm::cos(time));
  if (new_radius >= MIN_RADIUS && new_radius <= MAX_RADIUS) {
    radius_ = new_radius;
  }

  // Hit left or right wall
  if (x_ - radius_ <= 0) {
    vx_ *= -1;
    x_ = radius_;
  } else if (x_ + radius_ >= window_size) {
    vx_ *= -1;
    x_ = window_size - radius_;
  }

  // Hit top or bottom wall
  if (y_ - radius_ <= 0) {
    vy_ *= -1;
    y_ = radius_;
  } else if (y_ + radius_ >= window_size) {
    vy_ *= -1;
    y_ = window_size - radius_;
  }
}

bool Circle::is_point_inside(const double px, const double py) {
  double dx = px - x_;
  double dy = py - y_;
  return glm::sqrt((dx * dx) + (dy * dy)) <= radius_;
}

int Circle::add_vertices_to_buffer(GLfloat* buffer, const int start_pos) {
  for (int i = 0; i < VERT_ELEMENT_CNT; i += 3) {
    double ang = SLICE * i;
    buffer[start_pos + i] =     (radius_ * glm::cos(ang) + x_) * RETINA_SCALE;
    buffer[start_pos + i + 1] = (radius_ * glm::sin(ang) - y_) * RETINA_SCALE;
    buffer[start_pos + i + 2] = 0.0f;
  }

  return VERT_ELEMENT_CNT;
}
