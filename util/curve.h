#ifndef CURVE_H
#define CURVE_H

#include "gl_util.h"

struct BezierCurve {
  static glm::vec3 quadraticAt(glm::vec3 A, glm::vec3 B, glm::vec3 C, float t) {
    glm::vec3 D = glm::mix(A, B, t);
    glm::vec3 E = glm::mix(B, C, t);
    return glm::mix(D, E, t);
  }

  static glm::vec3 cubicAt(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 D,
                           float t) {
    glm::vec3 E = glm::mix(A, B, t);
    glm::vec3 F = glm::mix(B, C, t);
    glm::vec3 G = glm::mix(C, D, t);
    return quadraticAt(E, F, G, t);
  }

  static glm::vec3 at(std::vector<glm::vec3> control_points, float t) {
    while (control_points.size() > 1) {
      std::vector<glm::vec3> temp;
      for (size_t i = 1; i < control_points.size(); i++) {
        temp.push_back(glm::mix(control_points[i - 1], control_points[i], t));
      }
      control_points = move(temp);
    }
    return control_points[0];
  }
};

struct Spline {
  Spline(std::vector<glm::vec3> points) : control_points_(points) {}
  Spline() = default;
  void addControlPoint(glm::vec3 point) { control_points_.push_back(point); }
  void setPointsPerCurve(size_t control_points_per_curve) {
    control_points_per_curve_ = control_points_per_curve;
  }
  glm::vec3 at(float t) {
    int num_curves =
        (control_points_.size() - 1) / (control_points_per_curve_ - 1);
    float f = t * num_curves;
    int i = f;
    if (i == num_curves) i -= 1;
    float t0 = f - i;

    return BezierCurve::at(
        std::vector<glm::vec3>(
            control_points_.begin() + i * (control_points_per_curve_ - 1),
            control_points_.begin() + i * (control_points_per_curve_ - 1) +
                control_points_per_curve_),
        t0);
  }

 private:
  std::vector<glm::vec3> control_points_;
  size_t control_points_per_curve_{3};
};

#endif
