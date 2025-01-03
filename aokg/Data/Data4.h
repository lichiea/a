#pragma once
#include <windows.h>
#include <vector>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include "Camera.h"
#include "GraphicObject.h"
#include "Simulation.h"

extern LARGE_INTEGER frequency;  // Частота таймера
extern LARGE_INTEGER lastCounter; // Последний отсчет
extern float simulationTime; // Время симуляции
extern float frameTime;      // Время между кадрами
extern int frameCount;       // Счетчик кадров
extern int fps;            // Количество FPS
extern LARGE_INTEGER lastFPSCounter; // Последний отсчет для FPS
//// список графических объектов
extern std::vector<GraphicObject> graphicObjects;
//// используемая камера
extern Camera cam;
//// функция для инициализации всех общих данных (камера, объекты и т.д.)
void initData();
