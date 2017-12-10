#include <GL/glut.h>

//функция для отрисовки "круга" из чайников

void circleTeapot() {
	glTranslatef(0, -0.5, 0);
	glutSolidTeapot(0.5);
	glTranslatef(0, 0.5, 0);

	glTranslatef(0, 0, 2);
	glutSolidTeapot(0.5);

	glTranslatef(0, 0, -2); //0.0

	glTranslatef(0, 0, -2);
	glutSolidTeapot(0.5);
	glTranslatef(0, 0, 2); //0.0

	glTranslatef(0, 1, -2.5);
	glutSolidTeapot(0.5);
	glTranslatef(0, -1, 2.5); //0.0

	glTranslatef(0, 1, 2.5);
	glutSolidTeapot(0.5);
	glTranslatef(0, -1, -2.5);//0.0

	glTranslatef(0, 2, 2.5);
	glutSolidTeapot(0.5);
	glTranslatef(0, -2, -2.5);//0 0

	glTranslatef(0, 2, -2.5);
	glutSolidTeapot(0.5);
	glTranslatef(0, -2, 2.5);//0 0

	glTranslatef(0, 3, -1.5);
	glutSolidTeapot(0.5);
	glTranslatef(0, -3, 1.5);

	glTranslatef(0, 3, 1.5);
	glutSolidTeapot(0.5);
	glTranslatef(0, -3, -1.5);

	glTranslatef(0, 3.5, 0);
	glutSolidTeapot(0.5);
}
void torusAndTeapot() {
	glRotated(85, 0, 1, 0);
	glutWireTeapot(1);
	glRotated(-90, 0, 1, 0);
	glRotated(70, 0, 1, 0);
	glutWireTorus(2, 5, 20, 20);
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//circleTeapot();
	torusAndTeapot();
	
	glPopMatrix();
	
	
	glFlush();

}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
}

int main(int argc, char * argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB);
	glutCreateWindow("hello, teapot!");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10.0, 1.0, 0.0,   // смотрим "из"
		0, 0, 0, //смотрим "на"
		0.0, 1.0, 0.0); // положение вверх
	glutMainLoop();
}
