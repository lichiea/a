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
vector<GraphicObject*> graphicObjects;
vector<shared_ptr<PhongMaterial>> materials;
//// используемая камера
Camera cam;
Light light;
// задание всех параметров одного материала
PhongMaterial material;

//// функция для инициализации всех общих данных (камера, объекты и т.д.)
void initData()
{

    initializeTiming();
    cam.setPosition(vec3(20, 15, 17.5));
    light.setPosition(vec4(20.0,20.0,15.0,1.0));
    light.setAmbient(vec4( 1.0, 1.0, 1.0, 1.0 ));
    light.setDiffuse(vec4(1.0, 1.0, 1.0, 1.0));
    light.setSpecular (vec4(1.0, 1.0, 1.0, 1.0));
    for (int i = 0; i < 4; ++i) {
        float ug;
        vec3 temp;
        if (i == 0) { ug = 0; temp = vec3(-5, 0, 0);}
        if (i == 1){ug = 180; temp = vec3(5, 0, 0);}
        if (i == 2) { ug = 90; temp = vec3(0, 0, 5);}
        if (i == 3) { ug = 270; temp = vec3(0, 0, -5); }
        // Создаем новый объект GraphicObject
        GraphicObject* tempGraphicObject = new GraphicObject();
        shared_ptr<PhongMaterial> material = make_shared<PhongMaterial>();
        // Загрузка материала
        material->load("data//materials//material_" +to_string(i+1) + ".txt");

        // Установка параметров для каждого объекта
        tempGraphicObject->setPosition(temp);
        tempGraphicObject->setAngle(ug);
        tempGraphicObject->setСolor(vec3(1, 1, 1));
        tempGraphicObject->setMaterial(material);
        materials.push_back(material);
        graphicObjects.push_back(tempGraphicObject);
    }
}
