#pragma once
#include <windows.h>
#include <vector>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include<memory>
#include"Mesh.h"
#include "Camera.h"
#include "GraphicObject.h"
#include "GameObject.h"
#include "Simulation.h"
#include "Light.h"
#include "MazeGenerator.h"
#include "PhongMaterial.h"
#include "GameObjectFactory.h"

extern LARGE_INTEGER frequency;  // Частота таймера
extern LARGE_INTEGER lastCounter; // Последний отсчет
extern float simulationTime; // Время симуляции
extern float frameTime;      // Время между кадрами
extern int frameCount;       // Счетчик кадров
extern int fps;            // Количество FPS
extern LARGE_INTEGER lastFPSCounter; // Последний отсчет для FPS
//// список графических объектов
extern std::vector<shared_ptr<GraphicObject>> graphicObjects;

// список игровых объектов расположенных на карте
extern shared_ptr<GameObject> mapObjects[21][21];
extern shared_ptr<GameObject> player;
// графический объект для плоскости (частный случай)
extern GraphicObject planeGraphicObject;
//// используемая камера
extern Camera cam;
extern Light light;
extern PhongMaterial material;
extern Mesh mesh;
//// функция для инициализации всех общих данных (камера, объекты и т.д.)
void initData();
extern GameObjectFactory gameObjectFactory;
extern int passabilityMap[21][21];
