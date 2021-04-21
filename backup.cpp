#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <iostream>

const GLfloat lightPosition1[4] = {0.0f, 3.0f, 5.0f, 1.0f};
const GLfloat green[] = {0.0, 1.0, 0.0, 1.0};
const GLfloat lightPosition2[4] = {5.0f, 3.0f, 0.0f, 1.0f};
const GLfloat red[] = {1.0, 0.0, 0.0, 1.0};

void setup(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, red);
    glLightfv(GL_LIGHT0, GL_SPECULAR, red);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, green);
    glLightfv(GL_LIGHT1, GL_SPECULAR, green);
}

void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glutSolidTeapot(0.5);
    glFlush();
}


void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,
        (double)width / height,
        0.1,
        100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-0.5, 2.1, 2.0,
        0.0, 0.0, 0.0,
        0.0, 4.0, 0.0);
}
void display(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glFlush();
}


int main(int argc, char* argv[])
{
    // insert code here...
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    //    glutCreateWindow("Wire_teapot");
    glutReshapeFunc(resize);
    glutDisplayFunc(draw);
    setup();
    glutMainLoop();
    return 0;
}
