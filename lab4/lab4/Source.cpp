//GLFW
#define _CRT_SECURE_NO_WARNINGS
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
using namespace std;

/*       Функция для чтения текстового файла в выделенный буфер char */
char* filetobuf(char *file)
{
	FILE *fptr;
	long length;
	char *buf;
	fptr = fopen(file, "rb"); /* Открываем файл для чтения */
	if (!fptr) /* Возвращаем NULL в случае ошибки */
		return NULL;
	fseek(fptr, 0, SEEK_END); /* Находим конец файла */
	length = ftell(fptr); /* Вычисляем размер файла в байтах */
	buf = (char*)malloc(length + 1); /* Выделяем буфер на единицу больше для файла и нулевого
									 указателя */
	fseek(fptr, 0, SEEK_SET); /* Переходим обратно на начало файла */
	fread(buf, length, 1, fptr); /* Считываем содержимое файла в буфер */
	fclose(fptr); /* Закрываем файл */
	buf[length] = 0; /* Ставим нулевой указатель в качестве метки конца буфера */
	return buf; /* Возвращаем полученный буфер */
}

//razmerj
const GLuint WIDTH = 800, HEIGHT = 600;
//shaders
/*
const char* vertexShaderSourse = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
*/
/*
const char* fragmentShaderSourse = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(0.0, 0.5, 0.2, 1.0);\n"
"}\0";
*/

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "SimpleShader", NULL, NULL);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
	//shader compilation
	// vertex shader
	//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	char* vertexSourse = filetobuf("vertexShaderSourse.qwerty");
	std::string str(vertexSourse);
	std::cout << str;
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (GLchar**)&vertexSourse, NULL);
	free(vertexSourse);
	glCompileShader(vertexShader);

	//check for errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR: SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";
	}
	cout << "hello" << endl;
	// fragment shader
	char* fragmentSourse = filetobuf("fragmentShaderSourse.qwerty");
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (GLchar**)&fragmentSourse, NULL);
	glCompileShader(fragmentShader);
	//check for errors

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR: SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << "\n";
	}

	//Linking shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR: Linking shader program\n" << infoLog << "\n";
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLint nVertex = 3;
	float vertices[] = {
		-0.5, -0.5, 0.0,
		0.5, -0.5, 0.0,
		0.0, 0.5, 0.0
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2, 0.4, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, nVertex);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}