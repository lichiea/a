#pragma once

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

// КЛАСС ДЛЯ РАБОТЫ С КАМЕРОЙ
class Camera
{
public:
	// конструкторы
	Camera();
	// установка и получение позиции камеры
	void setPosition(vec3 position);
	vec3 getPosition();
	float getAngleX();
	float getAngleY();
	float getR();
	//функции для перемещения камеры
	void rotateLeftRight(float degree);
	void rotateUpDown(float degree);
	void zoomInOut(float distance);
	// функция для установки матрицы камеры
	void apply();
	~Camera() {};
private:
	// перерасчет позиции камеры после поворотов
	void recalculatePosition();
private:
	// радиус и углы поворота
	float r;
	float angleX;
	float angleY;
	// позиция камеры
	vec3 position;
};
