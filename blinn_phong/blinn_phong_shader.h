#ifndef BLINN_PHONG_SHADER_H
#define BLINN_PHONG_SHADER_H
#include <algorithm>
#include <memory>

#include "blinn_phong_object.h"
#include "util/curve.h"
#include "util/gl_util.h"
#include "util/light.h"
#include "util/program.h"
#include "util/texture.h"
#include "util/transformation.h"

struct BlinnPhongShader {
  BlinnPhongShader(const char* object_file, const char* texture_file)
      : program_({"blinn_phong/blinn_phong.vs", "blinn_phong/blinn_phong.tcs",
                  "blinn_phong/blinn_phong.tes", "blinn_phong/blinn_phong.fs"},
                 {GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER,
                  GL_TESS_EVALUATION_SHADER, GL_FRAGMENT_SHADER}),
        object_(object_file),
        texture_(texture_file),
        transformation_(50.0f, 4.0f / 3.0f, 0.01f, 100.0f) {
    initGlobal();
    glPatchParameteri(GL_PATCH_VERTICES, 3);
    initTransformation();
    initCurves();
    selectSubroutine();
  }

  void display() {
    program_.bind();
    texture_.bind(program_.id(), "texture_sampler");
    bindTransformation();
    bindLight(glm::vec3(5.0, 4.0, 6.0), glm::vec3(1.0, 1.0, 1.0));
    object_.bind(program_.id());
    object_.display();
    // clean up the vertex array attributes.
    object_.unbind();
    frame_idx_++;
  }

 private:
  // Initialize the model, view and projection matrix.
  void initTransformation() {
    // TODO: allow user to change view using the mouse or keyboard.
    glm::vec3 look_from = glm::vec3(5.5f, 5.5f, 5.5f);
    glm::vec3 look_at = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    transformation_.setView(look_from, look_at, up);
  }

  void initCurves() {
    curves_.addControlPoint(glm::vec3{-3.0, 0, -3.0});
    curves_.addControlPoint(glm::vec3{3.0, 0, -1.0});
    curves_.addControlPoint(glm::vec3{3.0, 0, 3.0});
    curves_.addControlPoint(glm::vec3{-3.0, 0, 1.0});
    curves_.addControlPoint(glm::vec3{-3.0, 0, -3.0});
  }

  void bindTransformation() {
    float t = (frame_idx_ % 1000) * 0.001;
    glm::vec3 dvec = curves_.at(t);
    transformation_.translateToOrigin();
    transformation_.translate(dvec);
    GLuint model_view_matrix_id =
        glGetUniformLocation(program_.id(), "model_view");

    glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE,
                       &(transformation_.modelView()[0][0]));
    GLuint projection_matrix_id =
        glGetUniformLocation(program_.id(), "projection");
    glUniformMatrix4fv(projection_matrix_id, 1, GL_FALSE,
                       &(transformation_.projection()[0][0]));

    GLuint MVP_matrix_id = glGetUniformLocation(program_.id(), "MVP");
    glUniformMatrix4fv(MVP_matrix_id, 1, GL_FALSE,
                       &(transformation_.MVP()[0][0]));
  }

  void bindLight(glm::vec3 light_position_world_space, glm::vec3 color) {
    light_ = std::make_unique<Light>(light_position_world_space, color);
    light_->bind(program_.id(), transformation_.view());
  }

  void selectSubroutine() {
    GLuint subroutine_id = glGetSubroutineIndex(
        program_.id(), GL_FRAGMENT_SHADER, "gamma_correction");
    glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &subroutine_id);
  }

  void initGlobal() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glEnable(GL_CLIP_DISTANCE0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  Program program_;
  BlinnPhongObject object_;
  Texture texture_;
  std::unique_ptr<Light> light_;
  Transformation transformation_;
  Spline curves_;
  size_t frame_idx_{};
};

#endif