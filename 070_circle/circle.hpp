#include "point.hpp"

class Circle {
 private:
  Point center;
  const double radius;

 public:
  Circle(Point point, double radius) : center(point), radius(radius) {}
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
