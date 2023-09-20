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

GLfloat r[4], g[4], b[4]; // 색
GLfloat rb[4], gb[4], bb[4]; // 배경색
GLfloat pointx[4], pointy[4], length[4], height[4]; //사각형
GLfloat pointxb[4], pointyb[4], lengthb, heightb; //배경
//GLfloat backgc[3];

float randomnum(float a, float b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(a, b);
    return dis(gen);
}

int main(int argc, char* argv[])
{
    // 윈도우 생성
    glutInit(&argc, argv); // glut 초기화
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
    glutInitWindowPosition(WIN_x, WIN_y); // 윈도우의 위치 지정
    glutInitWindowSize(WIN_w, WIN_h); // 윈도우의 크기 지정
    glutCreateWindow("Example2"); // 윈도우 생성(윈도우 이름)

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else std::cout << "GLEW Initialized\n";

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 바탕색을 ‘blue’ 로 지정
    reset();
    glutDisplayFunc(drawScene); // 출력 함수의 지정
    glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
    glutMouseFunc(Mouse); // 마우스 입력
    srand(time(NULL)); // 난수 생성을 위한 초기화

    glutMainLoop(); // 이벤트 처리 시작
}

// 사각형 초기화
void reset() {
    for (int i = 0; i < 4; ++i) {
        r[i] = randomnum(0.0, 1.0);
        g[i] = randomnum(0.0, 1.0);
        b[i] = randomnum(0.0, 1.0);
        rb[i] = randomnum(0.0, 1.0);
        gb[i] = randomnum(0.0, 1.0);
        bb[i] = randomnum(0.0, 1.0);
        length[i] = 200;
        height[i] = 200;
    }
    pointx[0] = 200; pointx[1] = 600; pointx[2] = 200; pointx[3] = 600;
    pointy[0] = 200; pointy[1] = 200; pointy[2] = 600; pointy[3] = 600;
    pointxb[0] = 200; pointxb[1] = 600; pointxb[2] = 200; pointxb[3] = 600;
    pointyb[0] = 200; pointyb[1] = 200; pointyb[2] = 600; pointyb[3] = 600;
    lengthb = 200; heightb = 200;
    //backgc[0] = 1.0f;
    //backgc[1] = 1.0f;
    //backgc[2] = 1.0f;
}



//--- 콜백 함수: 그리기 콜백 함수 
GLvoid drawScene()
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 바탕색을 ‘blue’ 로 지정
    glClear(GL_COLOR_BUFFER_BIT); // 현재 색상을 사용하여 화면을 지운다. // glRectf는 화면 정중앙을 원점으로 그린다
    //배경
    for (int i = 0; i < 4; ++i) {
        glColor3f(rb[i], gb[i], bb[i]);
        glRectf((pointxb[i] - lengthb) / 400 - 1.0f, -((pointyb[i] + heightb) / 400 - 1.0f), (pointxb[i] + lengthb) / 400 - 1.0f, -((pointyb[i] - heightb) / 400 - 1.0f));
    }
    // 사각형
    for (int i = 0; i < 4; ++i) {
        glColor3f(r[i], g[i], b[i]);
        glRectf((pointx[i] - length[i]) / 400 - 1.0f, -((pointy[i] + height[i]) / 400 - 1.0f), (pointx[i] + length[i]) / 400 - 1.0f, -((pointy[i] - height[i]) / 400 - 1.0f));
    }
    glutSwapBuffers(); // 화면에 출력하기
}
// 마우스 클릭 이벤트 
GLvoid Mouse(int button, int state, int x, int y)
{
    int ga = 0;
    if (x > 400)ga += 1;
    if (y > 400)ga += 2;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { // 좌클릭이 감지되면 클릭된 영역을 판별하고 색상을 변경
        bool out = true;
        for (int i = 0; i < 4; ++i) {
            if ((pointx[i] - length[i]) < x && x < (pointx[i] + length[i]) && (pointy[i] - height[i]) < y && y < (pointy[i] + height[i])) {
                r[i] = randomnum(0.0, 1.0);
                g[i] = randomnum(0.0, 1.0);
                b[i] = randomnum(0.0, 1.0);
                out = false;
                break;
            }
        }
        if (out) {
            for (int i = 0; i < 4; ++i) {
                if (ga == i) {
                    rb[i] = randomnum(0.0, 1.0);
                    gb[i] = randomnum(0.0, 1.0);
                    bb[i] = randomnum(0.0, 1.0);
                }
      
            }
        }
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        int n = 0;
        if (x > WIN_w / 2)  n += 1;
        if (y > WIN_h / 2)  n += 2;

        //사격형 내부일 경우
        if ((pointx[n] - length[n]) < x && x < (pointx[n] + length[n]) && (pointy[n] - height[n]) < y && y < (pointy[n] + height[n])) {
            length[n] -= 10;
            height[n] -= 10;
            if (length[n] <= 0 || height[n] <= 0) { //예외처리
                length[n] += 10;
                height[n] += 10;
            }
        }

        //사각형 밖일 경우
        else {
            length[n] += 10;
            height[n] += 10;
            if (length[n] > 200 || height[n] > 200) { //예외처리
                length[n] -= 10;
                height[n] -= 10;
            }
        }
    }
    glutPostRedisplay(); // 다시 그리기 요청
}


GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}