#ifndef SPRING_MASS_SHADER_H
#define SPRING_MASS_SHADER_H

#include <vector>

#include "spring_mass_object.h"
#include "util/program.h"

struct SpringMassShader {
  SpringMassShader()
      : program_({"spring_mass/spring_mass.vs", "spring_mass/spring_mass.fs"},
                 {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER}) {}
  Program program_;
  SpringMassObject object_();
};

#endif