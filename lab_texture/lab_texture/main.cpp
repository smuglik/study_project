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

/*       ������� ��� ������ ���������� ����� � ���������� ����� char */
char* filetobuf(char *file)
{
	FILE *fptr;
	long length;
	char *buf;
	errno_t err = fopen_s(&fptr, file, "rb"); /* ��������� ���� ��� ������ */
	if (!fptr) /* ���������� NULL � ������ ������ */
		return NULL;
	fseek(fptr, 0, SEEK_END); /* ������� ����� ����� */
	length = ftell(fptr); /* ��������� ������ ����� � ������ */
	buf = (char*)malloc(length + 1); /* �������� ����� �� ������� ������ ��� ����� � ��������
									 ��������� */
	fseek(fptr, 0, SEEK_SET); /* ��������� ������� �� ������ ����� */
	fread(buf, length, 1, fptr); /* ��������� ���������� ����� � ����� */
	fclose(fptr); /* ��������� ���� */
	buf[length] = 0; /* ������ ������� ��������� � �������� ����� ����� ������ */
	return buf; /* ���������� ���������� ����� */
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

	unsigned int ourTexture1, ourTexture2;
	// �������� 1
	//----------
	glGenTextures(1, &ourTexture1);
	glBindTexture(GL_TEXTURE_2D, ourTexture1);
	//��������� ���������� ������������� ��������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	//��������� ���������� ����������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//-----------------------
	int width, height, numberChannels;
	//--------------------------
	stbi_set_flip_vertically_on_load(true); // ���������� �������� �� ��� Y
	//----------------
	unsigned char *data = stbi_load("grass.jpg", &width, &height, &numberChannels, 0);
	//----------------
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	// �������� 2
	glGenTextures(1, &ourTexture2);
	glBindTexture(GL_TEXTURE_2D, ourTexture2);
	//��������� ���������� ������������� ��������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	//��������� ���������� ����������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	data = stbi_load("itmo_logo_transp_en.png", &width, &height, &numberChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 1);
	/*glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture2"), 1);
	*/
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
		glUseProgram(shaderProgram);
		//����������� �������� � ���������������
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ourTexture1);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture1"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, ourTexture2);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture2"), 1);

		//���������� ��������� ���������
		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, nVertex);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}