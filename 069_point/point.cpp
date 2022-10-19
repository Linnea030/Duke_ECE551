#include "point.hpp"

#include <cmath>

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  return std::sqrt(std::pow(p.x - x, 2) + std::pow(p.y - y, 2));
}
