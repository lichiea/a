pragma once
#include <windows.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>

using namespace glm;
using namespace std;

// Структура, описывающая одну вершину полигональной сетки
// каждая вершина имеет геометрические координаты,
// вектор нормали и текстурные координаты
struct Vertex
{
	// геометрические координаты
	GLfloat coord[3];
	// вектор нормали
	GLfloat normal[3];
	// текстурные координаты нулевого текстурного блока
	GLfloat texCoord[2];
};

// КЛАСС ДЛЯ РАБОТЫ C МЕШЕМ
class Mesh
{
public:
	// конструктор
	Mesh();
	// загрузка меша из файла с указанным именем
	void load(string filename);
	// вывод меша (передача всех вершин в OpenGL)
	void draw();
	void form_v(vector<vec3> v, vector<vec3> n, vector<vec2> t, vector<ivec3> fPoints);
private:
	// массив вершин полигональной сетки
	vector<Vertex> vertices;
};
