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
Light light;
// задание всех параметров одного материала
PhongMaterial material;

//// функция для инициализации всех общих данных (камера, объекты и т.д.)
void initData()
{

    // задание всех параметров одного материала
    PhongMaterial material;
    //material.setDiffuse(vec4(1.0, 0.0, 0.0, 1.0));
    //material.setAmbient(vec4(0.4, 0.0, 0.0, 1.0));
    //material.setSpecular(vec4(0.0, 0.0, 0.0, 1.0));
    //material.setEmission(vec4(0.0, 0.0, 0.0, 1.0));
    //material.setShininess(64.0);
    //material.apply();

    GraphicObject tempGraphicObject;
    initializeTiming();
    cam.setPosition(vec3(20, 15, 17.5));
    light.setPosition(vec4(20.0,20.0,15.0,1.0));
    // 1 -----------------------------------------
    material.load("data//materials//material_1.txt");
    material.apply();
    tempGraphicObject.setPosition(vec3(-5, 0, 0));
    tempGraphicObject.setAngle(0.0);
    tempGraphicObject.setСolor(vec3(1, 0, 0));
    tempGraphicObject.setMaterial(&material);
    graphicObjects.push_back(tempGraphicObject);
    // 2 -----------------------------------------
    //material.load("data//materials//material_2.txt");
    //material.apply();
    tempGraphicObject.setPosition(vec3(5, 0, 0));
    tempGraphicObject.setAngle(180.0);
    tempGraphicObject.setСolor(vec3(1, 0, 0));
    //tempGraphicObject.setMaterial(&material);
    graphicObjects.push_back(tempGraphicObject);
    // 3 -----------------------------------------
    //material.load("data//materials//material_3.txt");
    //material.apply();
    tempGraphicObject.setPosition(vec3(0, 0, 5));
    tempGraphicObject.setAngle(90.0);
    tempGraphicObject.setСolor(vec3(1, 0, 0));
    //tempGraphicObject.setMaterial(&material);
    graphicObjects.push_back(tempGraphicObject);
    // 4 -----------------------------------------
    //material.load("data//materials//material_4.txt");
    //material.apply();
    tempGraphicObject.setPosition(vec3(0, 0, -5));
    tempGraphicObject.setAngle(270.0);
    tempGraphicObject.setСolor(vec3(1, 0, 0));
    //tempGraphicObject.setMaterial(&material);
    graphicObjects.push_back(tempGraphicObject);

}
