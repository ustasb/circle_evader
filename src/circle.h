#ifndef CIRCLE_H
#define CIRCLE_H

#include <GL/glew.h>

class Circle {
 public:
   Circle(double x, double y, double radius, double vx, double vy);
   //Circle(const Circle& other) = delete;

   void update(const double time, const int window_size_);
   int add_vertices_to_buffer(GLfloat* buffer, int start_pos);
   bool is_point_inside(const double px, const double py);
 private:
   double radius_;
   double vx_;
   double vy_;
   double x_;
   double y_;
};

#endif
