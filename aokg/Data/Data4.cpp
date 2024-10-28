#include "Data.h"
//// используемые пространства имен
using namespace glm;
using namespace std;

LARGE_INTEGER frequency;  // Частота таймера
LARGE_INTEGER lastCounter; // Последний отсчет
float simulationTime; // Время симуляции
float frameTime;      // Время между кадрами
int frameCount;       // Счетчик кадров
int fps;            // Количество FPS
LARGE_INTEGER lastFPSCounter; // Последний отсчет для FPS

//// список графических объектов
vector<GraphicObject> graphicObjects;
//// используемая камера
Camera cam;
//// функция для инициализации всех общих данных (камера, объекты и т.д.)
void initData()
{
    GraphicObject tempGraphicObject;
    initializeTiming();
    cam.setPosition(vec3(20, 15, 17.5));
    // 1 -----------------------------------------
    tempGraphicObject.setPosition(vec3(-5, 0, 0));
    tempGraphicObject.setAngle(0.0);
    tempGraphicObject.setСolor(vec3(0, 0, 1));
    graphicObjects.push_back(tempGraphicObject);
    // 2 -----------------------------------------
    tempGraphicObject.setPosition(vec3(5, 0, 0));
    tempGraphicObject.setAngle(180.0);
    tempGraphicObject.setСolor(vec3(1, 0, 0));
    graphicObjects.push_back(tempGraphicObject);
    // 3 -----------------------------------------
    tempGraphicObject.setPosition(vec3(0, 0, 5));
    tempGraphicObject.setAngle(90.0);
    tempGraphicObject.setСolor(vec3(1, 1, 1));
    graphicObjects.push_back(tempGraphicObject);
    // 4 -----------------------------------------
    tempGraphicObject.setPosition(vec3(0, 0, -5));
    tempGraphicObject.setAngle(270.0);
    tempGraphicObject.setСolor(vec3(0, 1, 0));
    graphicObjects.push_back(tempGraphicObject);
}
