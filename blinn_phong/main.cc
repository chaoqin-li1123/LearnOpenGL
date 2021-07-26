

#include "gl_util.h"
#include "shader.h"

// Global setting for 3d shader.
void initGlobal() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  // glEnable(GL_CULL_FACE);
}

GLFWwindow* initWindow(const char* window_name) {
  glewExperimental = true;
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    exit(-1);
  }
  // Antialiasing
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window.
  GLFWwindow* window = glfwCreateWindow(1024, 768, window_name, NULL, NULL);

  // Initialize GLEW
  glfwMakeContextCurrent(window);
  glewExperimental = true;
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    exit(-1);
  }
  return window;
}

int main(int argc, char** argv) {
  GLFWwindow* window = initWindow("monkey_head");
  initGlobal();

  Shader shader("blinn_phong/blinn_phong.vert", "blinn_phong/blinn_phong.frag",
                "input/suzanne.obj", "input/uvmap.DDS");
  CheckBoardShader background(0.3);
  do {
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //
    shader.display();
    background.display();

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }  // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0);
  glfwTerminate();
  return 0;
}