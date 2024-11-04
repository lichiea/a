#include "Camera.h"

Camera::Camera() {};
// установка позиции камеры
void Camera::setPosition(vec3 position)
{
	// определяем радиус - расстояние от начала системы координат до заданной позиции
	r = length(position);
	// определяем вертикальный угол:
	// это угол между вектором из начала координат к наблюдателю (v1)
	// и проекцией этого вектора на горизонтальную плоскость (v2)
	// для определения угла используется скалярное произведение нормализованных векторов
	vec3 v1 = position;
	vec3 v2 = vec3(v1.x, 0, v1.z);
	float cos_y = dot(normalize(v1), normalize(v2));
	angleY = degrees(acos(cos_y));
	// аналогичным образом определяем горизонтальный угол:
	// это угол между проекцией (v2) и единичным вектором вдоль оси Ox
	float cos_x = dot(normalize(v2), vec3(1, 0, 0));
	angleX = degrees(acos(cos_x));
	// пересчитываем позицию (для корректировок ошибок округления)
	recalculatePosition();
}

vec3 Camera::getPosition() {return position;}
float Camera::getAngleX() { return angleX; }
float Camera::getAngleY() { return angleY; }
float Camera::getR() { return r; }
//функции для перемещения камеры

void Camera::rotateLeftRight(float degree) {
	angleY =getAngleY() + degree;
	recalculatePosition();
}

void Camera::rotateUpDown(float degree) {
	float oldX = getAngleX();
	angleX = getAngleX()+degree;
	if ((angleX >= 5) && (angleX <= 85)) {
		recalculatePosition();
	}
	else {
		angleX = oldX;
		recalculatePosition();
	}
}

void Camera::zoomInOut(float distance) {
	float oldR = getR();
	r = getR() + distance;
	if ((r >= 15) && (r <= 60)) {
		recalculatePosition();
	}
	else {
		r = oldR;
		recalculatePosition();
	}
}

void Camera::apply(){
	glLoadIdentity();
	gluLookAt(getPosition().x, getPosition().y, getPosition().z, 0, 0, 0, 0, 1, 0);
}

void Camera::recalculatePosition() {
	vec3 eye;
	eye.x = r * cos(radians(angleY)) * cos(radians(angleX));
	eye.y = r * sin(radians(angleX));
	eye.z = r * sin(radians(angleY)) * cos(radians(angleX));
	position = eye;
	apply();
}
