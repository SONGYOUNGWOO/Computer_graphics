#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <iostream>
#include <random>

using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
void reset();

const double WIN_x = 500, WIN_y = 0;
const double WIN_w = 800, WIN_h = 800;

GLfloat r[4], g[4], b[4];                           // ��
GLfloat pointx[4], pointy[4], length[4], height[4]; // �簢�� ���� �߾Ӱ��� ���� �Ÿ���
GLfloat backgc[3];


void randomset() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0, 1.0);
    float a = dis(gen); // a�� ������ , float�� ����
    //std::uniform_int_distribution<int> dis(0, 100);
    //int b = dis(gen);
    cout << "a = " << a << endl;
    //cout << "b = " << b << endl;
}

int main(int argc, char* argv[])
{
    // ������ ����
    glutInit(&argc, argv);                          // glut �ʱ�ȭ
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);   // ���÷��� ��� ����
    glutInitWindowPosition(WIN_x, WIN_y);           // �������� ��ġ ����
    glutInitWindowSize(WIN_w, WIN_h);               // �������� ũ�� ����
    glutCreateWindow("Example2");                   // ������ ����(������ �̸�)

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else std::cout << "GLEW Initialized\n";

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // �������� ��blue�� �� ����
    reset();                    //�簢�� �ʱ�ȭ + ��
    randomset();                //�����ʱ�ȭ
    glutDisplayFunc(drawScene); // ��� �Լ��� ����
    glutReshapeFunc(Reshape);   // �ٽ� �׸��� �Լ� ����
    glutMouseFunc(Mouse);       // ���콺 �Է�
    srand(time(NULL));          // ���� ������ ���� �ʱ�ȭ
    glutMainLoop();             // �̺�Ʈ ó�� ����
}

// �簢�� �ʱ�ȭ
void reset() {
    for (int i = 0; i < 4; ++i) {
        r[i] = (float)rand() / (float)RAND_MAX;
        g[i] = (float)rand() / (float)RAND_MAX;
        b[i] = (float)rand() / (float)RAND_MAX;
        length[i] = 200;
        height[i] = 200;
    }
    pointx[0] = 200; pointx[1] = 600; pointx[2] = 200; pointx[3] = 600;
    pointy[0] = 200; pointy[1] = 200; pointy[2] = 600; pointy[3] = 600;
    //���� �ʱ�ȭ
    backgc[0] = 1.0f;
    backgc[1] = 1.0f;
    backgc[2] = 1.0f;
}



//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
GLvoid drawScene()
{
    glClearColor(backgc[0], backgc[1], backgc[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);               // ���� ������ ����Ͽ� ȭ���� �����. 
    for (int i = 0; i < 4; ++i) {
        glColor3f(r[i], g[i], b[i]);
        // glRectf�� ȭ�� ���߾��� �������� �׸���
        glRectf((pointx[i] - length[i]) / 400 - 1.0f, -((pointy[i] + height[i]) / 400 - 1.0f), (pointx[i] + length[i]) / 400 - 1.0f, -((pointy[i] - height[i]) / 400 - 1.0f));
    }
    glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
// ���콺 Ŭ�� �̺�Ʈ 
GLvoid Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { // ��Ŭ���� �����Ǹ� Ŭ���� ������ �Ǻ��ϰ� ������ ����
        bool out = true;
        for (int i = 0; i < 4; ++i) {
            if ((pointx[i] - length[i]) < x && x < (pointx[i] + length[i]) && (pointy[i] - height[i]) < y && y < (pointy[i] + height[i])) {
                r[i] = (float)rand() / (float)RAND_MAX;
                g[i] = (float)rand() / (float)RAND_MAX;
                b[i] = (float)rand() / (float)RAND_MAX;
                out = false;
                break;
            }
        }
        if (out) {
            backgc[0] = (float)rand() / (float)RAND_MAX;
            backgc[1] = (float)rand() / (float)RAND_MAX;
            backgc[2] = (float)rand() / (float)RAND_MAX;
        }
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        int n = 0;
        if (x > WIN_w / 2)  n += 1;
        if (y > WIN_h / 2)  n += 2;

        //����� ������ ���
        if ((pointx[n] - length[n]) < x && x < (pointx[n] + length[n]) && (pointy[n] - height[n]) < y && y < (pointy[n] + height[n])) {
            length[n] -= 10;
            height[n] -= 10;
            if (length[n] <= 0 || height[n] <= 0) { //����ó��
                length[n] += 10;
                height[n] += 10;
            }
        }

        //�簢�� ���� ���
        else {
            length[n] += 10;
            height[n] += 10;
            if (length[n] > 200 || height[n] > 200) { //����ó��
                length[n] -= 10;
                height[n] -= 10;
            }
        }
    }
    glutPostRedisplay(); // �ٽ� �׸��� ��û
}


GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}