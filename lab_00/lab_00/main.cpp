#define _CRT_SECURE_NO_WARNINGS
#include "GL\freeglut.h" 
#include <cmath> 
#include <stdio.h>

using namespace std;
const int screenWidth = 640;  // Высота и ширина окна, в котором рисуется график 
const int screenHeight = 480;
GLdouble start_t = -30, end_t = 30, step_t = 0.01; // Диапазон отсчетов и шаг 
GLdouble start_y = -1, end_y = 1, step_y = 0.2;
GLdouble new_start_y = -30, new_end_y = 30;
GLdouble A = 1., w = 1.570796, p = 3.141593; //Параметры рисуемой функции 
void *Fount = GLUT_BITMAP_TIMES_ROMAN_24;

void setWindow(float left, float right, float bottom, float top) { //Мировое окно 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

void setViewport(int left, int right, int bottom, int top) { // Порт просмотра 
	glViewport(left, bottom, right - left, top - bottom);
}

void renderBitmapString(float x, float y, void *Fount, char *string) {
	glRasterPos2d(x, y);
	glutBitmapCharacter(Fount, *string);
}

void onDisplay() {
	setWindow(start_t, end_t, start_y, end_y);
	setViewport(0, screenWidth, 40, screenHeight - 40);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (GLdouble t = start_t; t < end_t; t += step_t) {
		GLdouble f = (sin(t)) / t;
		glVertex2d(t, f);
	}
	glEnd();

	setWindow(start_t, end_t, new_start_y, new_end_y);
	setViewport(0, screenWidth, 0, screenHeight);
	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2d(0, start_y * 30);
	glVertex2d(0, end_y * 30);

	glVertex2d(start_t, 0);
	glVertex2d(end_t, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2d(-1, 29);
	glVertex2d(1, 29);
	glVertex2d(0, 30);

	glVertex2d(29, 1);
	glVertex2d(29, -1);
	glVertex2d(30, 0);
	glEnd();
	renderBitmapString(-5, 27, Fount, "Y");
	renderBitmapString(27, 3, Fount, "X");
	//отрисовка подписей
	char ar[MAX_PATH];
	for (int i = -30; i <= 30; i += 2) {
		sprintf(ar, "%d", i);
		glRasterPos2d(-i, -2);
		glutBitmapString(GLUT_BITMAP_8_BY_13, (GLubyte*)ar);
	}
	GLint factor = 1;
	GLushort pattern = 0xAAAA;
	glEnable(GL_LINE_STIPPLE);

	// отрисовка сетки
	for (GLdouble i = -30; i <= 30; i = i + 2) {
		glLineStipple(factor, pattern);
		glBegin(GL_LINES);
		glVertex2f(i, -30);
		glVertex2f(i, 30);

		glVertex2f(-30, i);
		glVertex2f(30, i);
		glEnd();
	}
	glDisable(GL_LINE_STIPPLE);
	glutSwapBuffers();
}

void onReshape(int, int) {

}

void onMouse(int, int, int, int) {

}

void onKeyboard(unsigned char, int, int) {

}

void initExtra() {
	glClearColor(1., 1., 1., 0.); // Цвет фона белый 
								  //glColor3f(1., 0., 0.);  // Цвет рисования черный 
	glPointSize(2.);  // «Радиус» точки 2 пикселя 
	glMatrixMode(GL_PROJECTION);  // Функция, задающая ортографическую модель 
	glLoadIdentity();  // Установка единичной проекционной матрицы 
	gluOrtho2D(0, (GLdouble)screenWidth, 0, (GLdouble)screenHeight);

	glMatrixMode(GL_PROJECTION);  // Функция, задающая ортографическую модель 
	glLoadIdentity();  // Установка единичной проекционной матрицы 
	gluOrtho2D(1.0, 5.0, 2.5, 3.8); // Задание мирового окна 
	glViewport(0, 0, 640, 480);  // Задание порта просмотра 
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);  // Инициализация инструментария 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Установка режима отображения 
	glutInitWindowSize(640, 480);  // Установка размера окна 
	glutInitWindowPosition(200, 200);  // Положение окна на экране 
	glutCreateWindow("Basic application");  // Создание окна 
	glutDisplayFunc(onDisplay);  // Регистрация функций обратного  
	glutReshapeFunc(onReshape);  // вызова 
	glutMouseFunc(onMouse);   glutKeyboardFunc(onKeyboard);
	initExtra();  // Дополнительная инициализация (если необходимо) 
	glutMainLoop();  // Вход в главный рабочий цикл 
	return 0;
}