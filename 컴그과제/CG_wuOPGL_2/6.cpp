#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
void changeRandomColor();

const double WIN_x = 500, WIN_y = 0;
const double WIN_w = 800, WIN_h = 800;
int clickedRegion = -1; // Ŭ���� �簢�� ������ ��Ÿ���� ����
bool one = false;
bool two = false;
bool three = false;
bool four = false;

int main(int argc, char* argv[])
{
    // ������ ����
    glutInit(&argc, argv); // glut �ʱ�ȭ
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
    glutInitWindowPosition(WIN_x, WIN_y); // �������� ��ġ ����
    glutInitWindowSize(WIN_w, WIN_h); // �������� ũ�� ����
    glutCreateWindow("Example2"); // ������ ����(������ �̸�)

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else std::cout << "GLEW Initialized\n";

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // �������� ��blue�� �� ����

    glutDisplayFunc(drawScene); // ��� �Լ��� ����
    glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
    glutMouseFunc(Mouse); // ���콺 �Է�
    srand(time(NULL)); // ���� ������ ���� �ʱ�ȭ

    glutMainLoop(); // �̺�Ʈ ó�� ����
}

//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
GLvoid drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT); // ���� ������ ����Ͽ� ȭ���� �����.
    // glRectf�� ȭ�� ���߾��� �������� �׸���
    // 1�� �簢��
    float r = (float)rand() / (float)RAND_MAX;
    float g = (float)rand() / (float)RAND_MAX;
    float b = (float)rand() / (float)RAND_MAX;
    float r1 = r; float g1 = g; float b1 = b;
    if (clickedRegion == 1) {
        glColor3f(r, g, b); // ������ ����
    }
    else glColor3f(r1, g1, b1);
    glRectf(-WIN_w, 0.0f, 0.0f, WIN_h / 2);
    // 2�� �簢��
    if (clickedRegion == 2) {
        float r2 = r; float g2 = g; float b2 = b;
        glColor3f(r2, g2, b2); // ������ ����
    }
    glRectf(0.0f, 0.0f, WIN_w / 2, WIN_h / 2);

    // 3�� �簢��
    if (clickedRegion == 3) {
        float r3 = r; float g3 = g; float b3 = b;
        glColor3f(r3, g3, b3); // ������ ����
    }
    glRectf(-WIN_w / 2, -WIN_h / 2, 0.0f, 0.0f);

    // 4�� �簢��
    if (clickedRegion == 4) {
        float r4 = r; float g4 = g; float b4 = b;
        glColor3f(r4, g4, b4); // ������ ����
    }
    glRectf(0.0f, -WIN_h / 2, WIN_w / 2, 0.0f);

    glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

// ���콺 Ŭ�� �̺�Ʈ 
GLvoid Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // ��Ŭ���� �����Ǹ� Ŭ���� ������ �Ǻ��ϰ� ������ ����
        if (x < WIN_w / 2) {
            if (y < WIN_h / 2) {
                clickedRegion = 1;
            }
            else {
                clickedRegion = 3;
            }
        }
        else {
            if (y < WIN_h / 2) {
                clickedRegion = 2;
            }
            else {
                clickedRegion = 4;
            }
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        if (x < WIN_w / 2) {
            if (y < WIN_h / 2) {
                // clickedRegion = 1;
                one = true;
            }
            else {
                // clickedRegion = 3;
                three = true;
            }
        }
        else {
            if (y < WIN_h / 2) {
                // clickedRegion = 2;
                two = true;
            }
            else {
                // clickedRegion = 4;
                four = true;
            }
        }
    }
    glutPostRedisplay(); // �ٽ� �׸��� ��û
}


GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}