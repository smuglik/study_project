/*#include <stdio.h> 
#include <GL/glut.h> 

void init(void) { 
	glClearColor(0.9, 0.9, 0.9, 1.); 
}

void onReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, w / (float)h, 1.0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void onDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 0, -5, 0, 0, 0, 0, 1, 0);
	glRotatef(-30, 1, 0, 0);
	glColor3f(1, 0, 0);
	glutSolidTeapot(1);
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Hello World!");
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onReshape);
	init();
	glutMainLoop();
}*/

#include <GL/glut.h>

void display() {

	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT);

	/* future matrix manipulations should affect the modelview matrix */
	glMatrixMode(GL_MODELVIEW);

	/* draw scene */
	glPushMatrix();
	glPushMatrix();

	/*glTranslatef(1, 0, 0);
	glutWireTeapot(0.25);

	glTranslatef(1, 0, 0);
	glutWireTeapot(0.25);

	glTranslatef(-3, 0, 0);
	glutWireTeapot(0.25);

	glTranslatef(0, 1, 0);
	glutWireTeapot(0.25);

	glTranslatef(1, 1, 0);
	glutWireTeapot(0.25);*/

	glTranslatef(5, 1, 1);
	glutWireTeapot(1);
	

	/*glTranslatef(0, 2, 1);
	glutWireTeapot(0.25);
	glTranslatef(1, 1, -5);
	glutWireTeapot(0.25);
	glTranslatef(-1, 1, 0);
	glutWireTeapot(0.25);
	/*glTranslatef(-2, 0, 0);
	glutWireTeapot(0.25);*/
	/*glTranslatef(0, 0, -3);
	glutWireTeapot(1);                // middle teapot
	glTranslatef(0, 2, 0);
	glutSolidTeapot(1);               // top teapot
	glPopMatrix();

	glTranslatef(0, -2, -1);
	glutSolidTeapot(1);    */           // bottom teapot

	glPopMatrix();

	/* flush drawing routines to the window */
	glFlush();

}

void reshape(int width, int height) {

	/* define the viewport transformation */
	glViewport(0, 0, width, height);

}

int main(int argc, char * argv[]) {

	/* initialize GLUT, using any commandline parameters passed to the
	program */
	glutInit(&argc, argv);

	/* setup the size, position, and display mode for new windows */
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB);

	/* create and set up a window */
	glutCreateWindow("hello, teapot!");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	/* define the projection transformation */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 10);

	/* define the viewing transformation */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	/* tell GLUT to wait for events */
	glutMainLoop();
}