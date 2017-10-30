// sample_shader.cpp : Defines the entry point for the console application.
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

//razmerj
const GLuint WIDTH = 800, HEIGHT = 600;

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	int w1, h1, nrChannels1;
	unsigned char *data = stbi_load("grass.jpg", &w1, &h1, &nrChannels1, 0);
	int w2, h2, nrChannels2;
	unsigned char *data1 = stbi_load("smile.png", &w2, &h2, &nrChannels2, 0);

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

	// fragment shader
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

	GLuint texture1, texture2;
	// текстура 1
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w1, h1, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	// текстура 2
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w2, h2, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data1);
	glBindTexture(GL_TEXTURE_2D, 1);
	GLint nVertex = 12;

	float vertices[] = {
		0, 0, 0, 0, 1, 0, 0, 0,
		0.5, 0, 0, 0, 1, 0, 1, 0,
		0, 0.5, 0, 0, 1, 0, 0, 1,

		0.5, 0, 0, 0, 1, 0, 1, 0,
		0, 0.5, 0, 0, 1, 0, 0, 1,
		0.5, 0.5, 0, 0, 1, 0, 1, 1,

		-1, 0, 0, 0, 1, 0, 1, 0,
		-1, -0.5, 0, 0, 1, 0, 0, 0,
		-0.5, -0.5, 0, 0, 1, 0, 0, 1,

		-0.5, -0.5, 0, 0, 1, 0, 0, 1,
		-0.5, 0, 0, 0, 1, 0, 1, 1,
		-1, 0, 0, 0, 1, 0, 1, 0,

	};

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

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2, 0.4, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw triangle
		

		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;

		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture1"), 0);
		
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture2"), 0);

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