#include <Eigen/Core>
#include <cmath>
#include <iostream>

constexpr double PI = 3.14159;

Eigen::Vector3f translate(Eigen::Vector3f const& v, float const dx,
                          float const dy) {
  Eigen::Matrix3f transform = Eigen::Matrix3f::Identity();
  transform(0, 2) = dx, transform(1, 2) = dy;
  return transform * v;
}

Eigen::Vector3f rotate(Eigen::Vector3f const& v, double theta) {
  Eigen::Matrix3f transform = Eigen::Matrix3f::Identity();
  float cos_theta = cos(theta), sin_theta = sin(theta);
  transform(0, 0) = cos_theta, transform(0, 1) = -sin_theta;
  transform(1, 0) = sin_theta, transform(1, 1) = cos_theta;
  return transform * v;
}

int main() {
  Eigen::Vector3f p{2.0f, 1.0f, 1.0f};
  Eigen::Vector3f rotated = rotate(p, 45.0 / 180 * PI);
  Eigen::Vector3f translated = translate(rotated, 1.0f, 2.0f);
  std::cout << translated << std::endl;
  return 0;
}