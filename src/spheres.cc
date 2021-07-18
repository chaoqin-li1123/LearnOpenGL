#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include <cstdlib>

double rand_double() { return (double)rand() / RAND_MAX; }

void initLight() {
  GLfloat light_pos[4]{1.0, 1.0, 1.0, 0.0};
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void setMaterial() {
  GLfloat material_specular[4]{};
  for (int i = 0; i < 3; i++) {
    material_specular[i] = rand_double();
  }
  GLfloat material_shininess[4]{};
  for (int i = 0; i < 3; i++) {
    material_shininess[i] = rand_double();
  }
  glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
}

void init() {
  glShadeModel(GL_SMOOTH);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  initLight();
}

void display() {
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  setMaterial();
  glutSolidSphere(3.0, 20, 15);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GL_RGB | GLUT_DEPTH);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(1000, 1000);
  glutCreateWindow("spheres");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
}