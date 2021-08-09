#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <glm/ext/matrix_transform.hpp>

#include "gl_util.h"

struct Transformation {
  Transformation(float field_of_view, float aspect_ratio, float near_z,
                 float far_z)
      : projection_(glm::perspective(glm::radians(field_of_view), aspect_ratio,
                                     near_z, far_z)) {
    calculateModelViewProjection();
  }
  const glm::mat4& view() const { return view_; }
  const glm::mat4& model() const { return model_; }
  const glm::mat4& modelView() const { return model_view_; }
  const glm::mat4& MVP() const { return MVP_; }
  const glm::mat4& projection() const { return projection_; }
  void setView(glm::vec3 look_from, glm::vec3 look_at, glm::vec3 up) {
    view_ = glm::lookAt(look_from, look_at, up);
    calculateModelViewProjection();
  }

  void translate(glm::vec3 dvec) {
    model_ = glm::translate(model_, dvec);
    // model_[3][0] += dvec.x, model_[3][1] += dvec.y, model_[3][2] += dvec.z;
    calculateModelViewProjection();
  }

  void translateToOrigin() {
    model_ = glm::mat4(1.0);
    calculateModelViewProjection();
  }

  void calculateModelViewProjection() {
    model_view_ = view_ * model_;
    MVP_ = projection_ * model_view_;
  }

 private:
  glm::mat4 model_{1.0f};
  glm::mat4 model_view_;
  glm::mat4 view_{1.0f};
  glm::mat4 projection_;
  glm::mat4 MVP_;
};

#endif