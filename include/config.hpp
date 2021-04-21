#include <GLUT/GLUT.h>

int get_wx = glutGet(GLUT_WINDOW_X);  //window表示位置を取得
int get_wy = glutGet(GLUT_WINDOW_Y);
int get_ww = glutGet(GLUT_WINDOW_WIDTH);
int get_wh = glutGet(GLUT_WINDOW_HEIGHT);

int eps = 3;

int WIDTH = 960;
int HEIGHT = 720;
constexpr GLfloat len = 50;

GLfloat colors[][3] = {
    {0., 0., 1.},         //blue
    {0., 1., 0.},         //green
    {1., 1., 0},          //yellow
    {1., 1., 1.},         //white
    {0.9922, 0.4941, 0},  //orange
    {1., 0., 0.},         //red
    {0., 0., 0.}};

// 軸の描画
void drawAxis(void)
{
    glLineWidth(20.);
    static float axis_pos[] = {0.0f, 0.0f, 0.0f};
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(axis_pos[0], axis_pos[1], axis_pos[2]);
    glBegin(GL_LINES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);

    glEnd();
    glPopMatrix();
}
//ライトの位置
GLfloat lightpos[] = {1200.0, 150.0, -500.0, 1.0};
