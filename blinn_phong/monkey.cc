#include <glm/fwd.hpp>

#include "gl_util.hpp"

struct Shader {
  Shader() {
    initModel();
    initShaderProgram();
    initVertexArray();
    initVertexBuffer();
    initTexture();
    initUVBuffer();
    initNormalBuffer();
    initTransformation();
    initLight();
  }

  void initModel() { loadOBJ("input/suzanne.obj", vertices_, uvs_, normals_); }

  void initShaderProgram() {
    program_id_ = loadShaders("blinn-phong.vert", "blinn-phong.frag");
    glUseProgram(program_id_);
  }

  void initVertexArray() {
    glGenVertexArrays(1, &vertex_array_id_);
    glBindVertexArray(vertex_array_id_);
  }

  void initVertexBuffer() {
    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(glm::vec3),
                 &vertices_[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,         // attribute 0.
                          3,         // size
                          GL_FLOAT,  // type
                          GL_FALSE,  // normalized?
                          0,         // stride
                          (void *)0  // array buffer offset
    );
  }

  void initUVBuffer() {
    glGenBuffers(1, &uv_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer_);
    glBufferData(GL_ARRAY_BUFFER, uvs_.size() * sizeof(glm::vec2), &uvs_[0],
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,         // attribute 1.
                          2,         // size
                          GL_FLOAT,  // type
                          GL_FALSE,  // normalized?
                          0,         // stride
                          (void *)0  // array buffer offset
    );
  }

  void initNormalBuffer() {
    glGenBuffers(1, &normal_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_);
    glBufferData(GL_ARRAY_BUFFER, normals_.size() * sizeof(glm::vec3),
                 &normals_[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,         // attribute 1.
                          3,         // size
                          GL_FLOAT,  // type
                          GL_FALSE,  // normalized?
                          0,         // stride
                          (void *)0  // array buffer offset
    );
  }

  void initTexture() {
    texture_id_ = loadDDS("input/uvmap.DDS");
    GLuint texture_sampler_id =
        glGetUniformLocation(program_id_, "texture_sampler");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glUniform1i(texture_sampler_id, 0);
  }

  void initTransformation() {
    glm::mat4 model = glm::mat4(1.0f);

    glm::vec3 look_from = glm::vec3(4.0f, 4.0f, 4.0f);
    glm::vec3 look_at = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 view = glm::lookAt(look_from, look_at, up);

    model_view_ = view * model;
    GLuint model_view_matrix_id =
        glGetUniformLocation(program_id_, "model_view");
    glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, &model_view_[0][0]);

    float field_of_view = 50.0f;
    float aspect_ratio = 4.0f / 3.0f;
    float near_z = 1.0f, far_z = 100.0f;
    projection_ = glm::perspective(glm::radians(field_of_view), aspect_ratio,
                                   near_z, far_z);
    GLuint projection_matrix_id =
        glGetUniformLocation(program_id_, "projection");
    glUniformMatrix4fv(projection_matrix_id, 1, GL_FALSE, &projection_[0][0]);

    MVP_ = projection_ * model_view_;
    GLuint MVP_matrix_id = glGetUniformLocation(program_id_, "MVP");
    glUniformMatrix4fv(MVP_matrix_id, 1, GL_FALSE, &MVP_[0][0]);
  }

  void initLight() {
    glm::vec4 light_position_world_space(8.0, 4.0, 5.0, 1.0);
    light_position_camera_space_ = model_view_ * light_position_world_space;
    GLuint light_position_id =
        glGetUniformLocation(program_id_, "light_position_camera_space");
    glUniform3f(light_position_id, light_position_camera_space_.x,
                light_position_camera_space_.y, light_position_camera_space_.z);

    light_color_ = glm::vec3(1.0, 1.0, 0.0);
    GLuint light_color_id = glGetUniformLocation(program_id_, "light_color");
    glUniform3f(light_color_id, light_color_.x, light_color_.y, light_color_.z);
  }

  ~Shader() {
    glDeleteBuffers(1, &vertex_buffer_);
    glDeleteBuffers(1, &uv_buffer_);
    glDeleteTextures(1, &texture_id_);
    glDeleteProgram(program_id_);
    glDeleteVertexArrays(1, &vertex_array_id_);
    glfwTerminate();
  }
  void display() { glDrawArrays(GL_TRIANGLES, 0, vertices_.size()); }

 private:
  std::vector<glm::vec3> vertices_;
  std::vector<glm::vec2> uvs_;
  std::vector<glm::vec3> normals_;

  GLuint program_id_;
  GLuint texture_id_;
  GLuint vertex_buffer_, uv_buffer_, normal_buffer_;
  GLuint vertex_array_id_;

  glm::mat4 model_view_;
  glm::mat4 projection_;
  glm::mat4 MVP_;

  glm::vec3 light_position_camera_space_;
  glm::vec3 light_color_;
};

void initGlobal() {
  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);

  // Cull triangles which normal is not towards the camera
  glEnable(GL_CULL_FACE);
}

GLFWwindow *initWindow() {
  glewExperimental = true;  // Needed for core profile
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    exit(-1);
  }
  glfwWindowHint(GLFW_SAMPLES, 4);                // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // We want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE,
                 GLFW_OPENGL_CORE_PROFILE);  // We don't want the old OpenGL

  // Open a window and create its OpenGL context
  GLFWwindow *window = glfwCreateWindow(1024, 768, "Artist", NULL, NULL);

  glfwMakeContextCurrent(window);  // Initialize GLEW
  glewExperimental = true;         // Needed in core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    exit(-1);
  }
  return window;
}

int main(int argc, char **argv) {
  GLFWwindow *window = initWindow();
  Shader shader{};
  initGlobal();
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
  return 0;
}