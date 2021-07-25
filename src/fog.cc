#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

constexpr GLuint SET_MATERIAL = 1;

void initLight() {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  GLfloat light_pos[4]{1.0, 1.0, 1.0, 0.0};
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void initProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(50, 3.0, 3.0, -3.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void initFog() {
  GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0};
  glEnable(GL_FOG);
  glFogi(GL_FOG_MODE, GL_EXP);
  glFogfv(GL_FOG_COLOR, fogColor);
  glFogf(GL_FOG_DENSITY, 0.35);
  glHint(GL_FOG_HINT, GL_DONT_CARE);
  glFogf(GL_FOG_START, 1.0);
  glFogf(GL_FOG_END, 5.0);
}

void setMaterial() {
  GLfloat material_specular[3]{0.1745, 0.01175, 0.01175};
  GLfloat material_shininess[1]{50.0};
  glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
}

void init() {
  glClearColor(0.5, 0.5, 0.5, 1.0);
  glEnable(GL_DEPTH_TEST);
  initLight();
  initFog();
  initProjection();
  glNewList(SET_MATERIAL, GL_COMPILE);
  setMaterial();
  glEndList();
}

void drawTeapot(GLfloat x, GLfloat y, GLfloat z) {
  glPushMatrix();
  glTranslated(x, y, z);
  glutSolidTeapot(0.4);
  glPopMatrix();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glCallList(SET_MATERIAL);
  drawTeapot(0.0, 0.0, 0.0);
  drawTeapot(-1.0, -1.0, -2.0);
  drawTeapot(-2.0, -2.0, -4.0);
  glFlush();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1000, 1000);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("spheres in fog");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
}