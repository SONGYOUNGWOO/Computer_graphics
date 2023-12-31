#include <iostream>
#include <random>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y); 
GLvoid TimerFunction(int value);
//GLvoid RandomRGB();

GLclampf r = 1.0f;
GLclampf g = 1.0f;
GLclampf b = 1.0f;

static bool IsTimerAlive = true;

void main(int argc, char* argv[])			//--- 윈도우 출력하고 콜백함수 설정 
{											 
	glutInit(&argc, argv);					// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(0, 0);			// 윈도우의 위치 지정 
	glutInitWindowSize(800, 600);			// 윈도우의 크기 지정 
	glutCreateWindow("Example1");			// 윈도우 생성

	glewExperimental = GL_TRUE;				//--- GLEW 초기화하기
	if (glewInit() != GLEW_OK){				// glew 초기화
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	} else std::cout << "GLEW Initialized\n";

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// 바탕색을 ‘black’ 로 지정

	glutKeyboardFunc(Keyboard);				// 키보드 입력 콜백함수 지정
	glutDisplayFunc(drawScene);				// 출력 함수의 지정
	glutReshapeFunc(Reshape);				// 다시 그리기 콜백함수 지정
	glutMainLoop();							// 이벤트 처리 시작 
}
GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수; 
{ 
    glClear(GL_COLOR_BUFFER_BIT);			// 설정된 색으로 전체를 칠하기 // 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다
    glutSwapBuffers();						// 화면에 출력하기
}
GLvoid Reshape(int w, int h)				//--- 콜백 함수: 다시 그리기 콜백 함수 
{
	glViewport(0, 0, 800, 600);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'c' :
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		break;					//--- 배경색을 청록색으로 설정
	case 'm' : 
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		break;					//--- 배경색을 자홍색으로 설정
	case 'y' :
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f); 
		break;					//--- 배경색을 노랑색으로 설정
	case 'a' :
		glClearColor((float)rand()/(float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, 1.0f);
		break;					//랜덤색
	case 'w' : 
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
		break;					//백색
	case 'k' :
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
		break;					//검정색
	case 't' : 
		glutTimerFunc(100, TimerFunction, 1);
		IsTimerAlive = true;
		break;
		break;					//타이머를 설정하여 특정 시간마다 랜덤색으로 계속 바뀌게 한다.
	case 's' :
		IsTimerAlive = false;
		break;
		break;					//타이머 종료
	case 'q' : 
		exit(0) ; 
		break;									//프로그램종료
	}
	glutPostRedisplay();	//--- 배경색이 바뀔 때마다 출력 콜백 함수를 호출하여 화면을 refresh 한다
}
void TimerFunction(int value)
{
	glClearColor((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, 1.0f);
	glutPostRedisplay(); // 화면 재 출력
	if (IsTimerAlive) {
		glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정 반복
	}
}

