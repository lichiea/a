#pragma once
#include <windows.h>
#include <vector>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include "Camera.h"
#include "GraphicObject.h"
// список графических объектов
extern std::vector<GraphicObject> graphicObjects;
// используемая камера
extern Camera camera;
// функция для инициализации всех общих данных (камера, объекты и т.д.)
void initData();
