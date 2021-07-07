#include <GL/glut.h>

int w = 400, h = 400;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT, GL_LINE);
    glPolygonMode(GL_BACK, GL_LINE);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
}

void display()
{
    double xs[5]{0.0, 0.0, 0.4, 0.6, 0.4};
    double ys[5]{0.0, 0.3, 0.3, 0.15, 0.0};
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
    // glColor3f(0.0, 0.0, 1.0);
    for (int i = 0; i < 5; i++)
        glVertex2f(xs[i], ys[i]);
    glEnd();

    glBegin(GL_POLYGON);
    // glColor3f(1.0, 0.0, 0.0);
    for (int i = 4; i >= 0; i--)
        glVertex2f(xs[i], ys[i] - 0.3);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(w, h);

    init();

    glutCreateWindow("polygon");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}