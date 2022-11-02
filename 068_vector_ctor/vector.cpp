#include "vector.hpp"

#include <cmath>
#include <cstdio>
using namespace std;

/* write your class implementation in this file
 */
void Vector2D::initVector(double xi, double yi) {
  x = xi;
  y = yi;
}

double Vector2D::getMagnitude() const {
  double ans = sqrt(pow(x, 2) + pow(y, 2));
  return ans;
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D ans;
  ans.initVector(x + rhs.x, y + rhs.y);
  return ans;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}

double Vector2D::dot(const Vector2D & rhs) const {
  return x * rhs.x + y * rhs.y;
}

void Vector2D::print() const {
  printf("<%.2f, %.2f>", x, y);
}
