#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
void Vector2D::initVector(double init_x, double init_y) {
  x = init_x;
  y = init_y;
}
double Vector2D::getMagnitude() const {
  return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}
Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D res;
  res.initVector(rhs.x + this->x, rhs.y + this->y);
  return res;
}
Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x = x + rhs.x;
  y = y + rhs.y;
  return *this;
}
double Vector2D::dot(const Vector2D & rhs) const {
  return x * rhs.x + y * rhs.y;
}
void Vector2D::print() const {
  printf("<%.2f, %.2f>", x, y);
}