#include <GL/glut.h>

//функци€ дл€ отрисовки "круга" из чайников

void drawCircleTeapot() {
	glTranslatef(0, -0.5, 0);
	glutSolidTeapot(0.5);
	glTranslatef(0, 0.5, 0);

	glTranslatef(0, 0, 2);
	glutSolidTeapot(0.5);

	glTranslatef(0, 0, -2); //0 0

	glTranslatef(0, 0, -2);
	glutSolidTeapot(0.5);
	glTranslatef(0, 0, 2); //0 0

	glTranslatef(0, 1, -2.5);
	glutSolidTeapot(0.5);
	glTranslatef(0, -1, 2.5); //0 0

	glTranslatef(0, 1, 2.5);
	glutSolidTeapot(0.5);
	glTranslatef(0, -1, -2.5);//0 0

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

void drawTorusAndTeapot() {
	glRotated(85, 0, 1, 0);
	glutWireTeapot(1);
	glRotated(-90, 0, 1, 0);
	glRotated(70, 0, 1, 0);
	glutWireTorus(2, 5, 20, 20);
}

void drawParal() {
  glTranslatef(0, 0, 5);
  glutSolidCube(0.5);
  glTranslatef(0, 0, -5);
  glTranslatef(0, 0, 4.5);
  glutSolidCube(0.5);
  glTranslatef(0, 0, -4.5);
  glTranslatef(0, 0.2, 4.5);
  glutSolidCube(0.5);
  glTranslatef(0, -0.2, -4.5);

  glTranslatef(0, 0, 4.0);
  glutSolidCube(0.5);
  glTranslatef(0, 0, -4.0);
  glTranslatef(0, 0.2, 4.0);
  glutSolidCube(0.5);
  glTranslatef(0, -0.2, -4.0);
  glTranslatef(0, 0.4, 4.0);  // начало 3 €руса
  glutSolidCube(0.5);
  glTranslatef(0, -0.4, -4.0);

  glTranslatef(0, 0, 3.5);
  glutSolidCube(0.5);
  glTranslatef(0, 0, -3.5);
  glTranslatef(0, 0.2, 3.5);
  glutSolidCube(0.5);
  glTranslatef(0, -0.2, -3.5);
  glTranslatef(0, 0.4, 3.5);
  glutSolidCube(0.5);
  glTranslatef(0, -0.4, -3.5);
  glTranslatef(0, 0.6, 3.5); //начало 4 €руса
  glutSolidCube(0.5);
  glTranslatef(0, -0.6, -3.5);


  glTranslatef(0, 0, 3.0);
  glutSolidCube(0.5);
  glTranslatef(0, 0, -3.0);
  glTranslatef(0, 0.2, 3.0);
  glutSolidCube(0.5);
  glTranslatef(0, -0.2, -3.0);
  glTranslatef(0, 0.4, 3.0);
  glutSolidCube(0.5);
  glTranslatef(0, -0.4, -3.0);
  glTranslatef(0, 0.6, 3.0);
  glutSolidCube(0.5);
  glTranslatef(0, -0.6, -3.0);
  glTranslatef(0, 0.8, 3.0); //начало 5 €руса
  glutSolidCube(0.5);
  glTranslatef(0, -0.8, -3.0);

  glTranslatef(0, 0, 2.5);
  glutSolidCube(0.5);
  glTranslatef(0, 0, -2.5);
  glTranslatef(0, 0.2, 2.5);
  glutSolidCube(0.5);
  glTranslatef(0, -0.2, -2.5);
  glTranslatef(0, 0.4, 2.5);
  glutSolidCube(0.5);
  glTranslatef(0, -0.4, -2.5);
  glTranslatef(0, 0.6, 2.5);
  glutSolidCube(0.5);
  glTranslatef(0, -0.6, -2.5);
  glTranslatef(0, 0.8, 2.5);
  glutSolidCube(0.5);
  glTranslatef(0, -0.8, -2.5);
  glTranslatef(0, 1.0, 2.5);//начало 6 €руса
  glutSolidCube(0.5);
  glTranslatef(0, -1, -2.5);


  glTranslatef(0, 0, 2.0);
  glutSolidCube(0.5);
  glTranslatef(0, 0, -2.0);
  glTranslatef(0, 0.2, 2.0);
  glutSolidCube(0.5);
  glTranslatef(0, -0.2, -2.0);
  glTranslatef(0, 0.4, 2.0);
  glutSolidCube(0.5);
  glTranslatef(0, -0.4, -2.0);
  glTranslatef(0, 0.6, 2.0);
  glutSolidCube(0.5);
  glTranslatef(0, -0.6, -2.0);
  glTranslatef(0, 0.8, 2.0);
  glutSolidCube(0.5);
  glTranslatef(0, -0.8, -2.0);
  glTranslatef(0, 1, 2.0);
  glutSolidCube(0.5);
  glTranslatef(0, -1, -2.0);
  glTranslatef(0, 1.2, 2.0); //начало 7 €руса
  glutSolidCube(0.5);
  glTranslatef(0, -1.2, -2.0);

  glTranslatef(0, 0, 1.5);
  glutSolidCube(0.5);
  glTranslatef(0, 0, -1.5);
  glTranslatef(0, 0.2, 1.5);
  glutSolidCube(0.5);
  glTranslatef(0, -0.2, -1.5);
  glTranslatef(0, 0.4, 1.5);
  glutSolidCube(0.5);
  glTranslatef(0, -0.4, -1.5);
  glTranslatef(0, 0.6, 1.5);
  glutSolidCube(0.5);
  glTranslatef(0, -0.6, -1.5);
  glTranslatef(0, 0.8, 1.5);
  glutSolidCube(0.5);
  glTranslatef(0, -0.8, -1.5);
  glTranslatef(0, 1, 1.5);
  glutSolidCube(0.5);
  glTranslatef(0, -1, -1.5);
  glTranslatef(0, 1.2, 1.5);
  glutSolidCube(0.5);
  glTranslatef(0, -1.2, -1.5);
  glTranslatef(0, 1.4, 1.5);//nachalo 8
  glutSolidCube(0.5);
  glTranslatef(0, -1.4, -1.5);

  glTranslatef(0, 0, 1.0);
  glutSolidCube(0.5);
  glTranslatef(0, 0, -1.0);
  glTranslatef(0, 0.2, 1.0);
  glutSolidCube(0.5);
  glTranslatef(0, -0.2, -1.0);
  glTranslatef(0, 0.4, 1.0);
  glutSolidCube(0.5);
  glTranslatef(0, -0.4, -1.0);
  glTranslatef(0, 0.6, 1.0);
  glutSolidCube(0.5);
  glTranslatef(0, -0.6, -1.0);
  glTranslatef(0, 0.8, 1.0);
  glutSolidCube(0.5);
  glTranslatef(0, -0.8, -1.0);
  glTranslatef(0, 1, 1.0);
  glutSolidCube(0.5);
  glTranslatef(0, -1, -1.0);
  glTranslatef(0, 1.2, 1.0);
  glutSolidCube(0.5);
  glTranslatef(0, -1.2, -1.0);
  glTranslatef(0, 1.4, 1.0);
  glutSolidCube(0.5);
  glTranslatef(0, -1.4, -1.0);
  glTranslatef(0, 1.6, 1.0); //nachalo 9
  glutSolidCube(0.5);
  glTranslatef(0, -1.6, -1.0);


  glTranslatef(0, 0, 0.5);
  glutSolidCube(0.5);
  glTranslatef(0, 0, -0.5);
  glTranslatef(0, 0.2, 0.5);
  glutSolidCube(0.5);
  glTranslatef(0, -0.2, -0.5);
  glTranslatef(0, 0.4, 0.5);
  glutSolidCube(0.5);
  glTranslatef(0, -0.4, -0.5);
  glTranslatef(0, 0.6, 0.5);
  glutSolidCube(0.5);
  glTranslatef(0, -0.6, -0.5);
  glTranslatef(0, 0.8, 0.5);
  glutSolidCube(0.5);
  glTranslatef(0, -0.8, -0.5);
  glTranslatef(0, 1, 0.5);
  glutSolidCube(0.5);
  glTranslatef(0, -1, -0.5);
  glTranslatef(0, 1.2, 0.5);
  glutSolidCube(0.5);
  glTranslatef(0, -1.2, -0.5);
  glTranslatef(0, 1.4, 0.5);
  glutSolidCube(0.5);
  glTranslatef(0, -1.4, -0.5);
  glTranslatef(0, 1.6, 0.5);
  glutSolidCube(0.5);
  glTranslatef(0, -1.6, -0.5);
  glTranslatef(0, 1.8, 0.5); //nachalo 10
  glutSolidCube(0.5);
  glTranslatef(0, -1.8, -0.5);

  glTranslatef(0, 0, 0);
  glutSolidCube(0.5);
  glTranslatef(0, 0.2, 0);
  glutSolidCube(0.5);
  glTranslatef(0, -0.2, 0);
  glTranslatef(0, 0.4, 0);
  glutSolidCube(0.5);
  glTranslatef(0, -0.4, 0);
  glTranslatef(0, 0.6, 0);
  glutSolidCube(0.5);
  glTranslatef(0, -0.6, 0);
  glTranslatef(0, 0.8, 0);
  glutSolidCube(0.5);
  glTranslatef(0, -0.8, 0);
  glTranslatef(0, 1, 0);
  glutSolidCube(0.5);
  glTranslatef(0, -1, 0);
  glTranslatef(0, 1.2, 0);
  glutSolidCube(0.5);
  glTranslatef(0, -1.2, 0);
  glTranslatef(0, 1.4, 0);
  glutSolidCube(0.5);
  glTranslatef(0, -1.4, 0);
  glTranslatef(0, 1.6, 0);
  glutSolidCube(0.5);
  glTranslatef(0, -1.6, 0);
  glTranslatef(0, 1.8, 0);
  glutSolidCube(0.5);
  glTranslatef(0, -1.8, 0);
  glTranslatef(0, 2, 0); //nachalo 11
  glutSolidCube(0.5);
  glTranslatef(0, 2, 0);
 
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//drawCircleTeapot();
	//drawTorusAndTeapot();
  drawParal();
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
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("hello, teapot!");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(8.0, 1.0, 0.0,   // смотрим "из"
		0, 0, 0, //смотрим "на"
		0.0, 1.0, 0.0); // положение вверх
	glutMainLoop();
}
