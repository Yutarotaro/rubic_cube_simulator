#include <GLUT/GLUT.h>
#include <iostream>

#define PAI 3.14159265

//クォータニオン構造体
struct Quaternion {
    double w;
    double x;
    double y;
    double z;
};
//回転マトリックス
double Rotate[16];

Quaternion Target;
Quaternion current = {1.0, 0.0, 0.0, 0.0};

//演算子のオーバーロード Quaternionの積
Quaternion& operator*(Quaternion& q1, Quaternion& q2)
{
    Quaternion q0 = {
        q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
        q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
        q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
        q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w,
    };
    q1 = q0;
    return q1;
}
//クォータニオンから回転行列を算出
void qtor(double* r, Quaternion q)
{
    double xx = q.x * q.x * 2.0;
    double yy = q.y * q.y * 2.0;
    double zz = q.z * q.z * 2.0;
    double xy = q.x * q.y * 2.0;
    double yz = q.y * q.z * 2.0;
    double zx = q.z * q.x * 2.0;
    double xw = q.x * q.w * 2.0;
    double yw = q.y * q.w * 2.0;
    double zw = q.z * q.w * 2.0;
    double r1[16] = {1.0 - yy - zz, xy + zw, zx - yw, 0.0,
        xy - zw, 1.0 - zz - xx, yz + xw, 0.0,
        zx + yw, yz - xw, 1.0 - xx - yy, 0.0,
        0.0, 0.0, 0.0, 1.0};
    for (int i = 0; i < 16; i++) {
        r[i] = r1[i];
    }
}

int Mouse_X, Mouse_Y;

void mousemove(int x, int y)
{
    //移動量を計算
    double dx = (x - Mouse_X) * 1.33 / WIDTH;
    double dy = (y - Mouse_Y) * 1.0 / HEIGHT;

    //クォータニオンの長さ
    double length = sqrt(dx * dx + dy * dy);

    if (length != 0.0) {
        double radian = length * PAI;
        double theta = sin(radian) / length;
        Quaternion after = {cos(radian), dy * theta, dx * theta, 0.0};  //回転後の姿勢

        Target = after * current;

        qtor(Rotate, Target);
    }
}

void mouse(int button, int state, int x, int y)
{
    if (button) {
        switch (state) {
        case GLUT_DOWN:  //マウスボタンを押した位置を記憶
            Mouse_X = x;
            Mouse_Y = y;
            break;
        case GLUT_UP:  //姿勢を保存
            current = Target;
            break;
        default:
            break;
        }
    }
}
