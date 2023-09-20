#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <random>
#include <stdio.h>
using namespace std;
float return_number(float a, float b);

const int WIN_X = 10, WIN_Y = 10;
const int WIN_W = 800, WIN_H = 800;

// 마우스 상태 및 현재 선택된 사각형 
bool left_button = false;
int selected_rectangle = -1;

// 랜덤 색상 생성 함수
void randomset() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0, 1.0);
    //randomc = dis(gen); // randomc 색 설정
    std::uniform_real_distribution<float> dist(-1.0, 1.0);
   // randomsp = dist(gen); // randomsp 사각형 중앙 설정
}


struct Rectangle {
    GLfloat x, y; // 중심 좌표
    GLfloat size; // 크기
    GLfloat r, g, b; // 색상
};
struct Rectangle rect[5];
int n = 0;

// 새로운 사각형 추가 함수
void addRectangle() {

    if (n == 5) {
        for (int i = 0; i < 4; ++i) {
            rect[i].x = rect[i + 1].x;
            rect[i].y = rect[i + 1].y;
            rect[i].size = rect[i + 1].size;
            rect[i].r = rect[i + 1].r;
            rect[i].g = rect[i + 1].g;
            rect[i].b = rect[i + 1].b;
        }
        n--;
    }
    rect[n].x = return_number(-1.0, 1.0);
    rect[n].y = return_number(-1.0, 1.0);

    if (n == 0) {
        rect[n].x = 0;
        rect[n].y = 0;
    }
    rect[n].size = 40; 
    rect[n].r = return_number(0.0,1.0);
    rect[n].g = return_number(0.0,1.0);
    rect[n].b = return_number(0.0,1.0);
 
    n++;
}
// 그리기 콜백 함수
GLvoid drawScene()
{
    glClearColor(0.745f, 0.745f, 0.745f, 1.0f); // 회색을 바탕색을 설정
    glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

    for (int i = 0; i < n; ++i) {
        glColor3f(rect[i].r, rect[i].g, rect[i].b);
        glRectf(rect[i].x - rect[i].size/400, -(rect[i].y - rect[i].size/400), rect[i].x + rect[i].size/400, -(rect[i].y + rect[i].size/400));
    }
    glutSwapBuffers(); // 화면에 출력하기
}

//마우스 클릭 콜백 함수
void Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            left_button = true;
            float mx, my;
            mx = (float)x / 400 - 1.0f;
            my = (float)y / 400 - 1.0f;

            // 마우스 위치로부터 선택된 사각형 찾기
            selected_rectangle = -1;
            for (int i = 0; i < n; ++i) {
                if ((rect[i].x - rect[i].size/400) < mx && mx < (rect[i].x + rect[i].size/400) && (rect[i].y - rect[i].size/400) < my && my < (rect[i].y + rect[i].size/400))
                    selected_rectangle = i;
            }
            cout << selected_rectangle;
        }
         // 사각형 이동 상태 해제
        else {
            left_button = false;
            selected_rectangle = - 1;
        }       
    }
    glutPostRedisplay(); // 화면 다시 그리기 요청
}

//마우스 모션 콜백 함수
void Motion(int x, int y) {
    if (left_button && selected_rectangle != -1) {
        // 사각형을 마우스 위치로 이동
        float mx, my;
        mx = (float)x / 400 - 1.0f;
        my = (float)y / 400 - 1.0f;
        rect[selected_rectangle].x = mx;
        rect[selected_rectangle].y = my;
    }
    glutPostRedisplay(); // 화면 다시 그리기 요청
}

//키보드 입력 처리
GLvoid Keyboard(unsigned char key, int x, int y)
{
    // "a" 키를 누를 때마다 새로운 사각형 추가
    switch (key) {
    case 'a':
        addRectangle(); //사각형 추가
        break;
    }
    glutPostRedisplay(); // 화면 다시 그리기 요청
}

int main(int argc, char** argv)
{
    srand(static_cast<unsigned>(time(nullptr)));

    // 랜덤 값을 설정
    randomset();
    // 윈도우 생성
    glutInit(&argc, argv); // glut 초기화
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
    glutInitWindowPosition(WIN_X, WIN_Y); // 윈도우의 위치 지정
    glutInitWindowSize(WIN_W, WIN_H); // 윈도우의 크기 지정
    glutCreateWindow("Rectangle Moving"); // 윈도우 생성(윈도우 이름)

    glutDisplayFunc(drawScene); // 출력 함수의 지정
    glutMouseFunc(Mouse); // 마우스 입력
    glutMotionFunc(Motion); // 마우스 드래그 입력
    glutKeyboardFunc(Keyboard); // 키보드 입력

    glutMainLoop(); // 이벤트 처리 시작
}

float return_number(float a, float b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(a, b);
    return dis(gen);
}