#include <iostream>
#include <random>
#include <gl/glew.h> //--- �ʿ��� ������� include
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

void main(int argc, char* argv[])			//--- ������ ����ϰ� �ݹ��Լ� ���� 
{											 
	glutInit(&argc, argv);					// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(0, 0);			// �������� ��ġ ���� 
	glutInitWindowSize(800, 600);			// �������� ũ�� ���� 
	glutCreateWindow("Example1");			// ������ ����

	glewExperimental = GL_TRUE;				//--- GLEW �ʱ�ȭ�ϱ�
	if (glewInit() != GLEW_OK){				// glew �ʱ�ȭ
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	} else std::cout << "GLEW Initialized\n";

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// �������� ��black�� �� ����

	glutKeyboardFunc(Keyboard);				// Ű���� �Է� �ݹ��Լ� ����
	glutDisplayFunc(drawScene);				// ��� �Լ��� ����
	glutReshapeFunc(Reshape);				// �ٽ� �׸��� �ݹ��Լ� ����
	glutMainLoop();							// �̺�Ʈ ó�� ���� 
}
GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�; 
{ 
    glClear(GL_COLOR_BUFFER_BIT);			// ������ ������ ��ü�� ĥ�ϱ� // �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�
    glutSwapBuffers();						// ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h)				//--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
{
	glViewport(0, 0, 800, 600);
}

//void RandomRGB()
//{
//	r = (GLclampf)dist(eng);
//	g = (GLclampf)dist(eng);
//	b = (GLclampf)dist(eng);
//}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'c' :
		//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		r = 1.0f;
		g = 0.0f;
		b = 0.0f;
		break;					//--- ������ û�ϻ����� ����
	case 'm' : 
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		break;					//--- ������ ��ȫ������ ����
	case 'y' :
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f); 
		break;					//--- ������ ��������� ����
	case 'a' :
		glClearColor((float)rand()/(float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, 1.0f);
		break;					//������
	case 'w' : 
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
		break;					//���
	case 'k' :
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
		break;					//������
	case 't' : 
		glutTimerFunc(100, TimerFunction, 1);
		IsTimerAlive = true;
		break;
		break;					//Ÿ�̸Ӹ� �����Ͽ� Ư�� �ð����� ���������� ��� �ٲ�� �Ѵ�.
	case 's' :
		IsTimerAlive = false;
		break;
		break;					//Ÿ�̸� ����
	case 'q' : 
		exit(0) ; 
		break;									//���α׷�����
	}
	glutPostRedisplay();													//--- ������ �ٲ� ������ ��� �ݹ� �Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
}
void TimerFunction(int value)
{
	glClearColor((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, 1.0f);
	glutPostRedisplay(); // ȭ�� �� ���
	if (IsTimerAlive) {
		glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ���� �ݺ�
	}
}

