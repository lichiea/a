#include "Data.h"
//// используемые пространства имен
using namespace glm;
using namespace std;

int passabilityMap[21][21] = {
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,3,
3,0,2,1,2,0,2,0,2,2,2,1,2,0,2,0,2,0,2,2,3,
3,0,2,0,2,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,3,
3,0,1,0,2,2,1,2,2,0,2,0,2,2,2,1,2,0,2,0,3,
3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,3,
3,0,2,2,1,1,2,0,2,0,2,2,2,2,2,0,2,2,2,0,3,
3,0,2,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0,0,0,3,
3,0,2,0,2,2,2,0,2,0,2,2,1,2,2,2,1,2,2,0,3,
3,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0,0,0,1,0,3,
3,2,2,2,2,0,2,2,2,0,2,0,2,2,2,2,2,2,2,0,3,
3,0,0,0,2,0,0,0,1,0,2,0,0,0,2,0,0,0,0,0,3,
3,0,2,0,2,2,2,0,2,1,2,0,2,2,2,0,2,2,2,2,3,
3,0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,3,
3,2,2,2,2,0,2,2,2,0,2,2,2,0,1,0,2,2,2,0,3,
3,0,0,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,2,0,3,
3,0,2,0,2,1,2,0,2,0,2,2,2,0,2,2,2,0,2,0,3,
3,0,1,0,1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,3,
3,0,2,1,2,0,2,2,2,2,2,0,2,0,2,0,2,2,2,2,3,
3,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
};

LARGE_INTEGER frequency;  // Частота таймера
LARGE_INTEGER lastCounter; // Последний отсчет
float simulationTime; // Время симуляции
float frameTime;      // Время между кадрами
int frameCount;       // Счетчик кадров
int fps;            // Количество FPS
LARGE_INTEGER lastFPSCounter; // Последний отсчет для FPS

// список игровых объектов расположенных на карте
shared_ptr<GameObject> mapObjects[21][21];
// графический объект для плоскости (частный случай)
GraphicObject planeGraphicObject;
GameObject gobj;
//// список графических объектов
vector<shared_ptr<GraphicObject>> graphicObjects;
vector<shared_ptr<PhongMaterial>> materials;
// используемые меши
vector<shared_ptr<Mesh>> meshes;
//// используемая камера
Camera cam;
Light light;
Mesh mesh;
// задание всех параметров одного материала
PhongMaterial material;

//// функция для инициализации всех общих данных (камера, объекты и т.д.)
void initData()
{


    //m.load("data//meshes//SimplePlane.obj");
    //m.load("data//meshes//Box.obj");
    //m.load("data//meshes//ChamferBox.obj");
    //m.load("data//meshes//Sphere.obj");
    initializeTiming();
    cam.setPosition(vec3(20, 15, 17.5));
    light.setPosition(vec4(20.0,20.0,15.0,1.0));
    light.setAmbient(vec4(1.0, 1.0, 1.0, 1.0 ));
    light.setDiffuse(vec4(1.0, 1.0, 1.0, 1.0));
    light.setSpecular (vec4(1.0, 1.0, 1.0, 1.0));




    // Создаем новый объект GraphicObject
    GraphicObject tempGraphicObject1, tempGraphicObject2, tempGraphicObject3;

    shared_ptr<PhongMaterial> material = make_shared<PhongMaterial>();
    shared_ptr<Mesh> meshp = make_shared<Mesh>();

    //11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
    shared_ptr<PhongMaterial> material1 = make_shared<PhongMaterial>();
    material1->load("data//materials//material_2.txt");
    shared_ptr<Mesh> mesh1 = make_shared<Mesh>();
    mesh1->load("data//meshes//ChamferBox.obj");

    tempGraphicObject1.setMaterial(material1);
    tempGraphicObject1.setMesh(mesh1);
    meshes.push_back(mesh1);
    materials.push_back(material1);
    graphicObjects.push_back(make_shared<GraphicObject>(tempGraphicObject1));

    //22222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222
    shared_ptr<PhongMaterial> material2 = make_shared<PhongMaterial>();
    material2->load("data//materials//material_3.txt");
    shared_ptr<Mesh> mesh2 = make_shared<Mesh>();
    mesh2->load("data//meshes//Box.obj");
 
    tempGraphicObject2.setMaterial(material2);
    tempGraphicObject2.setMesh(mesh2);
    meshes.push_back(mesh2);
    materials.push_back(material2);
    graphicObjects.push_back(make_shared<GraphicObject>(tempGraphicObject2));

    //33333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333
    shared_ptr<PhongMaterial> material3 = make_shared<PhongMaterial>();
    shared_ptr<Mesh> mesh3 = make_shared<Mesh>();
    material3->load("data//materials//material_4.txt");
    mesh3->load("data//meshes//Box.obj");
    tempGraphicObject3.setMaterial(material3);
    tempGraphicObject3.setMesh(mesh3);
    meshes.push_back(mesh3);
    materials.push_back(material3);
    graphicObjects.push_back(make_shared<GraphicObject>(tempGraphicObject3));

    //4444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444
    material->load("data//materials//material_1.txt");
    meshp->load("data//meshes//SimplePlane.obj");
    planeGraphicObject.setMaterial(material);
    planeGraphicObject.setMesh(meshp);
    planeGraphicObject.setPosition(vec3(0.0, -0.5, 0.0));
    meshes.push_back(meshp);
    materials.push_back(material);
    for (int i = 0; i < 21; i++) {
           for (int j = 0; j < 21; j++) {
               shared_ptr<GameObject> obj = make_shared<GameObject>();
               obj->setPosition(i, j);
                if (passabilityMap[i][j] == 1) {
                    obj->setGraphicObject(tempGraphicObject1);
                }
                if (passabilityMap[i][j] == 2) {
                    obj->setGraphicObject(tempGraphicObject2);
                }
                if (passabilityMap[i][j] == 3) {
                    obj->setGraphicObject(tempGraphicObject3);
                }
                mapObjects[i][j] = obj;                
            }
        }
}
