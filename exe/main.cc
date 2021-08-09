

#include "blinn_phong/blinn_phong_shader.h"
#include "checkboard/checkboard_shader.h"
#include "spring_mass/spring_mass_shader.h"
#include "util/gl_util.h"

int main(int argc, char** argv) {
  GLFWwindow* window = initWindow("monkey_head");

  // BlinnPhongShader shader("input/suzanne.obj", "input/uvmap.DDS");
  CheckboardShader shader;
  do {
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.display();
    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }  // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0);
  glfwTerminate();
  return 0;
}