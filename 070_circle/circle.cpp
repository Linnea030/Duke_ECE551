#include "circle.hpp"

#include <cmath>
void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double sum = radius + otherCircle.radius;
  double Rs;
  double Rl;
  if (radius < otherCircle.radius) {
    Rl = otherCircle.radius;
    Rs = radius;
  }
  else {
    Rl = otherCircle.radius;
    Rs = radius;
  }
  double d = center.distanceFrom(otherCircle.center);
  double sub = Rl - Rs;
  if (d >= sum)
    return 0.0;
  else if (d <= sub)
    return M_PI * pow(Rs, 2);
  else {
    double ang1 = acos((Rl * Rl + d * d - Rs * Rs) / (2 * Rl * d));
    double ang2 = acos((Rs * Rs + d * d - Rl * Rl) / (2 * Rs * d));
    return ang1 * Rl * Rl + ang2 * Rs * Rs - Rl * d * sin(ang1);
  }
}
