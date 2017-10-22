//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//
//using namespace std;
//
//char* filetobuf(char *file) {
//	FILE *fptr;
//	long length;
//	char *buf;
//	fptr = fopen(file, "rb"); /* Открываем файл для чтения */
//	if (!fptr) /* Возвращаем NULL в случае ошибки */
//		return NULL;
//	fseek(fptr, 0, SEEK_END); /* Находим конец файла */
//	length = ftell(fptr); /* Вычисляем размер файла в байтах */
//	buf = (char*)malloc(length + 1); /* Выделяем буфер на единицу больше для файла и нулевого
//									 указателя */
//	fseek(fptr, 0, SEEK_SET); /* Переходим обратно на начало файла */
//	fread(buf, length, 1, fptr); /* Считываем содержимое файла в буфер */
//	fclose(fptr); /* Закрываем файл */
//	buf[length] = 0; /* Ставим нулевой указатель в качестве метки конца буфера */
//	return buf; /* Возвращаем полученный буфер */
//}
//int main() {
//	char* c = filetobuf("vertexShaderSource.txt");
//	return 0;
//}