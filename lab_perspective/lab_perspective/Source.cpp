// Лаба с перспективной камерой
//
//GLFW
#define _CRT_SECURE_NO_WARNINGS
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace glm;
using namespace std;

/*       Функция для чтения текстового файла в выделенный буфер char */
char* filetobuf(char *file)
{
	FILE *fptr;
	long length;
	char *buf;
	errno_t err = fopen_s(&fptr, file, "rb"); /* Открываем файл для чтения */
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

//Размеры
const GLuint WIDTH = 800, HEIGHT = 600;

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	int w1, h1, nrChannels;
	unsigned char *data = stbi_load("squad.jpg", &w1, &h1, &nrChannels, 0);

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
	
	//компиляция шейдера
	
	//вершинный шейдер 
	char* vertexSourse = filetobuf("vertexShaderSourse.txt");
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

	// фрагментный шейдер
	char* fragmentSourse = filetobuf("fragmentShaderSourse.txt");
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (GLchar**)&fragmentSourse, NULL);
	glCompileShader(fragmentShader);
	//check for errors

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR: SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << "\n";
	}

	//линковка шейдера
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

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w1, h1, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLint nVertex = 6; // количество вершин

	float vertices[] = {
		// грань 1
		0, 0, 0,  1, 0, 0,   0, 0,
		0.5, 0, 0,   0, 1, 0,  1, 0,
		0, 0.5, 0,   0, 0, 1,  0, 1,

		0.5, 0, 0,   0, 1, 0,  1, 0,
		0, 0.5, 0,   0, 0, 1,  0, 1,
		0.5, 0.5, 0,   0, 0, 1,  1, 1,

		//грань 2
		0.5, 0, 0,  0, 1, 0,  0, 0,
		0.5, 0, 0.5,   0, 1, 0,  0, 1,
		0.5, 0.5, 0.5,   0, 0, 1,  1, 1,

		0.5, 0.5, 0,   0, 0, 1,  1, 0,
		0.5, 0.5, 0.5,   0, 0, 1,  1, 1,
		0.5, 0, 0,  0, 1, 0,  0, 0,
		/////////////////////////////////////////////////////////////////////
		//грань 3
		0, 0.5, 0,  0, 0, 1,   0, 0,
		0, 0.5, 0.5,   0, 1, 0,  1, 0,
		0.5, 0.5, 0,   0, 0, 1,  0, 1,

		0.5, 0.5, 0,   0, 0, 1,  0, 1,
		0.5, 0.5, 0.5,   0, 0, 1,  1, 1,
		0, 0.5, 0.5,   0, 1, 0,  1, 0,

		//грань 4
		0, 0.5, 0,  0, 0, 1,   0, 1,
		0, 0.5, 0.5,   0, 1, 0,  1, 1,
		0, 0, 0,   1, 0, 0,  0, 0,

		0, 0, 0,   1, 0, 0,  0, 0,
		0, 0, 0.5,   0, 1, 0,  1, 0,
		0, 0.5, 0.5,   0, 1, 0,  1, 1,
		///////////////////////////////////////////////////////////////////////
		//грань 5
		0, 0, 0,  1, 0, 0,   0, 0,
		0.5, 0, 0,   0, 1, 0,  1, 0,
		0.5, 0, 0.5,   0, 1, 0,  1, 1,

		0, 0, 0,   1, 0, 0,  0, 0,
		0.5, 0, 0.5,   0, 1, 0,  1, 1,
		0, 0, 0.5,   0, 1, 0,  0, 1,

		//грань 6
		0, 0, 0.5,  0, 1, 0,   0, 0,
		0.5, 0, 0.5,   0, 1, 0,  1, 0,
		0.5, 0.5, 0.5,   0, 0, 1,  1, 1,

		0, 0, 0.5,   0, 1, 0,  0, 0,
		0, 0.5, 0.5,   0, 1, 0,  0, 1,
		0.5, 0.5, 0.5,   0, 0, 1,  1, 1,
	};

	mat4 model; //  модельная матрица
	model = rotate(model, radians(-45.0f), vec3(1.0f, 0.0f, 0.0f));
	mat4 view; // матрица вида
	// Сцена смещается в обратном направлении от того, куда мы хотим сместить камеру
	view = translate(view, vec3(0.0f, 0.0f, -3.0f));
	mat4 projection; // проекционная матрица
	projection = perspective<GLfloat>(radians(45.0f), (GLfloat)WIDTH /
		(GLfloat)HEIGHT, 0.1f, 100.0f);

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST); // тестирование буфера глубины
	
	while (!glfwWindowShouldClose(window)) { // главный цикл
		processInput(window);
		glClearColor(0.2, 0.4, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // добавление проверки буфера глубины
		// glClear(GL_COLOR_BUFFER_BIT);
		
		//отрисовка
		glUseProgram(shaderProgram);

		float timeValue = glfwGetTime()*0.5;
		float greenValue = sin(timeValue) / 2.0f + 0.5f;

		mat4 trans;
		trans = translate(trans, vec3(0.0, 0.0, 0.0));
		trans = rotate(trans, (float)glfwGetTime() / 2, vec3(1.0f, 1.0f, 1.0f));

		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(trans));

		/*int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 1.0f, greenValue, 0.0f, 1.0f);

		float positValue = sin(timeValue) / 2.0;
		int vertexPosLocation = glGetUniformLocation(shaderProgram, "pos");
		glUniform3f(vertexPosLocation, positValue, 0, 0);

		mat4 trans;
		trans = translate(trans, vec3(0.0, 0.0, 0.0));
		trans = rotate(trans, (float)glfwGetTime() * 50, vec3(0.0f, 1.0f, 0.0f));

		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(trans));*/

		int modelLoc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

		int viewLoc = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));

		int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 100); // КОЛ-ВО ВЕРШИН
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}