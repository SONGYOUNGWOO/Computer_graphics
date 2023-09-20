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
int clickedRegion = -1; // 클릭된 사각형 영역을 나타내는 변수
bool one = false;
bool two = false;
bool three = false;
bool four = false;

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

    glutDisplayFunc(drawScene); // 출력 함수의 지정
    glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
    glutMouseFunc(Mouse); // 마우스 입력
    srand(time(NULL)); // 난수 생성을 위한 초기화

    glutMainLoop(); // 이벤트 처리 시작
}

//--- 콜백 함수: 그리기 콜백 함수 
GLvoid drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT); // 현재 색상을 사용하여 화면을 지운다.
    // glRectf는 화면 정중앙을 원점으로 그린다
    // 1번 사각형
    float r = (float)rand() / (float)RAND_MAX;
    float g = (float)rand() / (float)RAND_MAX;
    float b = (float)rand() / (float)RAND_MAX;
    if (clickedRegion == 1) {
        glColor3f(r,g,b); // 랜덤한 색상
        if (one) { //줄어든 사각형
            glRectf(-WIN_w/4, 3*WIN_h /4, -WIN_w / 4,3*WIN_h / 4);
        }
        else {
            glRectf(-WIN_w, 0.0f, 0.0f, WIN_h / 2);
        }
    }
    // 2번 사각형
    if (clickedRegion == 2) {
        glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX); // 랜덤한 색상
    }
    else {
        glColor3f(0.0f, 1.0f, 0.0f); // green
    }
    glRectf(0.0f, 0.0f, WIN_w / 2, WIN_h / 2);

    // 3번 사각형
    if (clickedRegion == 3) {
        glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX); // 랜덤한 색상
    }
    else {
        glColor3f(1.0f, 0.0f, 0.0f); // red
    }
    glRectf(-WIN_w / 2, -WIN_h / 2, 0.0f, 0.0f);

    // 4번 사각형
    if (clickedRegion == 4) {
        glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX); // 랜덤한 색상
    }
    else {
        glColor3f(1.0f, 1.0f, 1.0f); // white
    }
    glRectf(0.0f, -WIN_h / 2, WIN_w / 2, 0.0f);

    glutSwapBuffers(); // 화면에 출력하기
}

// 마우스 클릭 이벤트 
GLvoid Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // 좌클릭이 감지되면 클릭된 영역을 판별하고 색상을 변경
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
    glutPostRedisplay(); // 다시 그리기 요청
}


GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}