#include "Eigen/Core"
#include "include/config.hpp"
#include "include/lib.hpp"
#include "omp.h"
#include <GLUT/glut.h>
#include <map>
#include <math.h>

struct Theta {
    float theta;
    float state;
};

class Rubic
{
private:
    int blue = 0;
    int green = 1;
    int yellow = 2;
    int white = 3;
    int orange = 4;
    int red = 5;
    int black = 6;

public:
    Eigen::Matrix3d A[6];

    Theta theta_1 = {.theta = 0., .state = 0.};
    Theta theta_4 = {.theta = 0., .state = 0.};
    Theta theta_5 = {.theta = 0., .state = 0.};

    const std::map<int, float> map_out = {
        {0, 0},
        {1, 180},
        {2, 90},
        {3, -90},
        {4, 90},
        {5, -90}};

    const std::map<int, float> map_in = {
        {0, 1},
        {1, 1},
        {2, 1},
        {3, 1},
        {4, 0},
        {5, 0}};


    const std::map<int, float> map_f = {
        {0, 0},
        {1, 0},
        {2, 1},
        {3, -1},
        {4, -1},
        {5, 1}};


    Rubic()
    {
        for (int i = 0; i < 6; i++) {
            A[i] = Eigen::MatrixXd::Constant(3, 3, i);
            //A[i](0, 2) = black;
            //A[i](1, 2) = black;
            //A[i](2, 2) = black;
        }
    }

    void sq(int x, int y, int z, int color)
    {
        glColor3f(colors[color][0], colors[color][1], colors[color][2]);
        glTranslatef(x, y, z);
        glRectf(-len / 2, -len / 2, len / 2, len / 2);
        glTranslatef(-x, -y, -z);
    }

    void rotate(Theta& a)
    {
    }

    void judge(Theta& a)
    {
        a.theta += 3.0 * a.state;
        if (!(int(a.theta) % 90)) {
            rotate(a);
            a.state = 0.;
        }
    }

    void display()
    {
#pragma omp parallel for
        for (int k = 0; k < 6; k++) {
            if (k == 4) {
                glRotatef(theta_4.theta, 0, 0, 0);
            } else if (k == 5) {
                glRotatef(theta_5.theta, 0, 0, 0);
            } else if (k == 1) {
                glRotatef(theta_1.theta, 0, 0, 1);
            }

            glRotatef(map_out.at(k), 0, ((k == 4 || k == 5) ? 1 : 0), 0);
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (j == 1) {
                        glRotatef(map_in.at(k) * theta_4.theta, 0, 0, 0);
                        if (k == orange) {
                            glRotatef(map_f.at(k) * theta_1.theta, 0, 0, 0);
                        }
                    } else if (j == -1) {
                        glRotatef(map_in.at(k) * theta_5.theta, 0, 0, 0);
                    }
                    if (i == -1) {
                        if (k == yellow) {
                            glRotatef(map_f.at(k) * theta_1.theta, 0, 1, 0);
                        }
                    }
                    if (i == 1) {
                        if (k == white) {
                            glRotatef(map_f.at(k) * theta_1.theta, 0, 1, 0);
                        }
                    }
                    if (j == -1) {
                        if (k == red) {
                            glRotatef(map_f.at(k) * theta_1.theta, 0, 0, 0);
                        }
                    }
                    sq((len + eps) * j, (len + eps) * i, 1.5 * len + eps, A[k](i + 1, j + 1));
                    if (j == 1) {
                        glRotatef(-map_in.at(k) * theta_4.theta, 0, 0, 0);
                        if (k == orange) {
                            glRotatef(-map_f.at(k) * theta_1.theta, 0, 0, 0);
                        }
                    } else if (j == -1) {
                        glRotatef(-map_in.at(k) * theta_5.theta, 0, 0, 0);
                    }
                    if (i == -1) {
                        if (k == yellow) {
                            glRotatef(-map_f.at(k) * theta_1.theta, 0, 1, 0);
                        }
                    }
                    if (i == 1) {
                        if (k == white) {
                            glRotatef(-map_f.at(k) * theta_1.theta, 0, 1, 0);
                        }
                    }
                    if (j == -1) {
                        if (k == red) {
                            glRotatef(-map_f.at(k) * theta_1.theta, 0, 0, 0);
                        }
                    }
                }
            }
            glRotatef(-map_out.at(k), 0, ((k == 4 || k == 5) ? 1 : 0), 0);

            if (k == 4) {
                glRotatef(-theta_4.theta, 0, 0, 0);
            } else if (k == 5) {
                glRotatef(-theta_5.theta, 0, 0, 0);
            } else if (k == 1) {
                glRotatef(-theta_1.theta, 0, 0, 1);
            }
        }
    }
};

Rubic Rb;

void display(void)
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 2 * WIDTH, 2 * HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //視野角,アスペクト比(ウィンドウの幅/高さ),描画する範囲(最も近い距離,最も遠い距離)
    gluPerspective(30.0, (double)WIDTH / (double)HEIGHT, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //視点の設定
    float a = 3.0;

    gluLookAt(150.0 * a, 100.0 * a, -200.0 * a,  //カメラの座標
        0.0, 0.0, 0.0,                           // 注視点の座標
        0.0, 1.0, 0.0);                          // 画面の上方向を指すベクトル

    //クォータニオンによる回転
    glMultMatrixd(Rotate);

    Rb.judge(Rb.theta_1);
    Rb.judge(Rb.theta_4);
    Rb.judge(Rb.theta_5);

    Rb.display();

    glutSwapBuffers();
}

void idle(void)
{
    glutPostRedisplay();
}

void Init()
{
    glClearColor(0.3, 0.3, 0.3, 0.0f);
    glEnable(GL_DEPTH_TEST);
    qtor(Rotate, current);
}

void move(unsigned char key)
{
}


void key(unsigned char key, int x, int y)
{
    switch (key) {
    case 'L':
        Rb.theta_4.state = 1.;
        break;
    case 'l':
        Rb.theta_4.state = -1.;
        break;
    case 'r':
        Rb.theta_5.state = 1.;
        break;
    case 'R':
        Rb.theta_5.state = -1.;
        break;
    case 'f':
        Rb.theta_1.state = 1.;
        break;
    case 'F':
        Rb.theta_1.state = -1.;
        break;
    default:
        break;
    }
}

int main(int argc, char* argv[])
{
    glutInitWindowPosition(500, 100);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemove);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    drawAxis();
    glutIdleFunc(idle);
    Init();
    glutMainLoop();
    return 0;
}
