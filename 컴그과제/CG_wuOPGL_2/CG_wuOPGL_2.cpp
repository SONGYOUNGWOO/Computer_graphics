#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <iostream>
#include <random>
using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);

const double WIN_x = 500, WIN_y = 0;
const double WIN_w = 800, WIN_h = 800;

GLfloat mx = 0.0f;
GLfloat my = 0.0f;

GLclampf r = 1.0f;
GLclampf g = 1.0f;
GLclampf b = 1.0f;


float randcolor = (float)rand() / (float)RAND_MAX;

int main(int argc, char*argv[])
{
	//윈도우 생성
	glutInit(&argc, argv);												// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);						// 디스플레이 모드 설정
	glutInitWindowPosition(WIN_x, WIN_y);								// 윈도우의 위치 지정
	glutInitWindowSize(WIN_w, WIN_h);									// 윈도우의 크기 지정
	glutCreateWindow("Example2");										// 윈도우 생성(윈도우 이름)

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else std::cout << "GLEW Initialized\n";

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);	// 바탕색을 ‘blue’ 로 지정

	
	glutDisplayFunc(drawScene);				// 출력 함수의 지정
	glutReshapeFunc(Reshape);				// 다시 그리기 함수 지정
	glutMouseFunc(Mouse);					// 마우스 입력
	glutMainLoop();							// 이벤트 처리 시작
}
//--- 콜백 함수: 그리기 콜백 함수 
GLvoid drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT); // 현재 색상을 사용하여 화면을 지운다.
	// glRectf는 화면 정중앙을 원점으로 그린다
	//glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
	glColor3f(0.0f, 0.0f, 1.0f); //blue
	glRectf(-WIN_w, 0.0f, 0.0f, WIN_h/2); //1

	//glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
	glColor3f(0.0f, 1.0f, 0.0f); //grean
	glRectf(0.0f, 0.0f, WIN_w/2, WIN_h/2); //2

	//glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
	glColor3f(1.0f, 0.0f, 0.0f); //red
	glRectf(-WIN_x/2, -WIN_h/2, 0.0f, 0.0f); //3

	//glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
	glColor3f(1.0f, 1.0f, 1.0f); //white
	glRectf(0.0f, -WIN_h/2, WIN_w/2, 0.0f); //4

	glutSwapBuffers();// 화면에 출력하기
	//glClear(GL_COLOR_BUFFER_BIT);			// **설정된 색**으로 전체를 칠하기 // 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다 중요함
}

//--- 콜백 함수: 다시 그리기 콜백 함수 
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, WIN_w, WIN_h);
}

GLvoid Mouse (int button, int state, int x, int y) // 마우스는 좌측상단을 원점으로 +방향으로 커진다
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		cout << "x= " << x << "y= " << y << endl;
		if (0 < x < WIN_w /2 && 0 < y < WIN_h / 2){//1

			if ( 0< x < 7 * WIN_w / 16 && 0 < y < 7 * WIN_h / 16) {
				glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
				//glRectf(-7 * WIN_w / 16, 16 && WIN_h / 16, -WIN_w / 16, 7 * WIN_h / 16); //1
				glutSwapBuffers();
			}
			else {
				glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
				glutSwapBuffers();
			}
		}
		else if (WIN_w / 2 < x < WIN_w  && 0< y < WIN_h / 2){//2

			if (WIN_w / 16 < 0 < 7 * WIN_w / 16 && 9* WIN_h / 16 < y < 15 * WIN_h / 16) {
				glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
				//glRectf(WIN_w / 16, WIN_h / 16, 7 * WIN_w / 16, 7 * WIN_h / 16); //2
				glutSwapBuffers();
			}
			else {
				glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
				glutSwapBuffers();
			}
		}
		else if (0 < x < WIN_w / 2 && WIN_h/2 < y < WIN_h){//3

			if (WIN_w / 16 < x < 7* WIN_w / 16 && 9*WIN_h / 16 < y <  15*WIN_h /16) {
				glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
				//glRectf(-7 * WIN_w / 16, -7 * WIN_h / 16, -WIN_w / 16, WIN_h / 16); //3
				glutSwapBuffers();
			}
			else {
				glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
				glutSwapBuffers();
			}
		}
		else if (WIN_w / 2 < x < WIN_w < x < 0 && WIN_h / 2 < y < WIN_h) {//4

			if (9 * WIN_w / 16 < 0 < 15 * WIN_w / 16 && 9 * WIN_h / 16 < y < 15 * WIN_h / 16) {
				glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
				//glRectf(WIN_w / 16, -7 * WIN_h / 16, 7 * WIN_w / 16, WIN_h / 16); //4
				glutSwapBuffers();
			}
			else {
				glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
				glutSwapBuffers();
			}
		}
		

	} // 우클릭 크기 축소,확대
	/*else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {



	}*/
}

// 사각형 그리기 //(x1, y1) : 좌측 하단 좌표값 (x2, y2): 우측 상단 좌표값 
//void glRectf (GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2); 
//{
//	glRectf(x1.f, y1.f, x2.f, y2.f);
//}

//GLvoid randomColor() {
//	float r = static_cast<float>(rand()) / RAND_MAX; 
//	float g = static_cast<float>(rand()) / RAND_MAX; 
//	float b = static_cast<float>(rand()) / RAND_MAX; 
//	glColor3f(r, g, b);
//}


//GLvoid Keyboard(unsigned char key, int x, int y)
//{
//	switch (key) {
//	case 'q':
//		exit(0);
//		break;
//
//	}
//}
//
//void Timer(int value)
//{
//	if (GetRectCorner().w >= 1.0f) direction = 2;
//	else if (GetRectCorner().z >= 1.0f) direction = 3;
//	else if (GetRectCorner().y <= -1.0f) direction = 4;
//	else if (GetRectCorner().x <= -1.0f) direction = 1;
//
//	if (direction == 1) {
//		mx += 0.01f;
//		my += 0.02f;
//	}
//	else if (direction == 2) {
//		mx += 0.02f;
//		my -= 0.01f;
//	}
//	else if (direction == 3) {
//		mx -= 0.01f;
//		my -= 0.02f;
//	}
//	else if (direction == 4) {
//		mx -= 0.02f;
//		my += 0.01f;
//	}
//	glutPostRedisplay(); // 화면 재 출력
//	if (IsTimerAlive)
//		glutTimerFunc(100, Timer, 1);
//}

//glClearColor(background_rgb.x, background_rgb.y, background_rgb.z, 1.0f);			// 바탕색을 설정
//glClear(GL_COLOR_BUFFER_BIT);														// 설정된 색으로 전체를 칠하기
//glColor3f(rect_rgb.x, rect_rgb.y, rect_rgb.z);
//glRectf(GetRectCorner().x, GetRectCorner().y, GetRectCorner().z, GetRectCorner().w);
//glutSwapBuffers();	
//GLvoid drawScene()	