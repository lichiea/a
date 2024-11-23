#include "Data.h"

//// используемые пространства имен
using namespace glm;
using namespace std;

void makeMap(int** matrix, int rows, int columns){
    int arr[21][21] = {0};

    auto maze = MazeGenerator::generate(20, 20);

    //MazeGenerator::print(maze);

    for (int j = 0; j < 20; j++) {
        for (int i = 0; i < 20; i++) {
            arr[i][j] = maze[i][j];
        }
    }

    // Устанавливаем границы
    for (int i = 0; i < 21; ++i) {
        arr[0][i] = 3;
        arr[21 - 1][i] = 3;
        arr[i][0] = 3;
        arr[i][21 - 1] = 3;
    }
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < columns; c++)
            matrix[r][c] = arr[r][c];
}

int passabilityMap[21][21]= {
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,3, //
3,0,2,1,2,0,2,0,2,2,2,1,2,0,2,0,2,0,2,2,3, //
3,0,2,0,2,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,3, //
3,0,1,0,2,2,1,2,2,0,2,0,2,2,2,1,2,0,2,0,3, //
3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,3, //
3,0,2,2,1,1,2,0,2,0,2,2,2,2,2,0,2,2,2,0,3, //
3,0,2,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0,0,0,3, //
3,0,2,0,2,2,2,0,2,0,2,2,1,2,2,2,1,2,2,0,3, //
3,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0,0,0,1,0,3, //
3,2,2,2,2,0,2,2,2,0,2,0,2,2,2,2,2,2,2,0,3, //
3,0,0,0,2,0,0,0,1,0,2,0,0,0,2,0,0,0,0,0,3, //
3,0,2,0,2,2,2,0,2,1,2,0,2,2,2,0,2,2,2,2,3, //
3,0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,3, //
3,2,2,2,2,0,2,2,2,0,2,2,2,0,1,0,2,2,2,0,3, //
3,0,0,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,2,0,3, //
3,0,2,0,2,1,2,0,2,0,2,2,2,0,2,2,2,0,2,0,3, //
3,0,1,0,1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,3, //
3,0,2,1,2,0,2,2,2,2,2,0,2,0,2,0,2,2,2,2,3, //
3,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,3, //
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
};

LARGE_INTEGER frequency;  // Частота таймера
LARGE_INTEGER lastCounter; // Последний отсчет
float simulationTime; // Время симуляции
float frameTime;      // Время между кадрами
int frameCount;       // Счетчик кадров
int fps;            // Количество FPS
LARGE_INTEGER lastFPSCounter; // Последний отсчет для FPS

// фабрика для создания игровых объектов
GameObjectFactory gameObjectFactory;
// список игровых объектов расположенных на карте
shared_ptr<GameObject> mapObjects[21][21];
// графический объект для плоскости (частный случай)
GraphicObject planeGraphicObject;
shared_ptr<GameObject> player;

//// список графических объектов
vector<shared_ptr<GraphicObject>> graphicObjects;

//// используемая камера
Camera cam;
Light light;
Mesh mesh;
// задание всех параметров одного материала
PhongMaterial material;

//// функция для инициализации всех общих данных (камера, объекты и т.д.)
void initData()
{

    gameObjectFactory.init("data//GameObjectsDescription.json");
    // выделяем память под матрицу
    int** matrix = new int* [21];
    for (int row = 0; row < 21; row++)
        matrix[row] = new int[21];
    makeMap(matrix, 21, 21);
    initializeTiming();
    cam.setPosition(vec3(30, 15, 17.5));
    light.setPosition(vec4(20.0,20.0,15.0,1.0));
    light.setAmbient(vec4(1.0, 1.0, 1.0, 1.0 ));
    light.setDiffuse(vec4(1.0, 1.0, 1.0, 1.0));
    light.setSpecular (vec4(1.0, 1.0, 1.0, 1.0));

    //4444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444
    shared_ptr<PhongMaterial> material = make_shared<PhongMaterial>();
    shared_ptr<Mesh> meshp = make_shared<Mesh>();
    material->load("data//materials//PlaneMaterial.txt");
    meshp->load("data//meshes//SimplePlane.obj");
    planeGraphicObject.setMaterial(material);
    planeGraphicObject.setMesh(meshp);
    planeGraphicObject.setPosition(vec3(0.0, -0.5, 0.0));


    // инициализация объектов сцены
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            switch (passabilityMap[i][j]) {
            default:
                break;
            case 1:
                mapObjects[i][j] = gameObjectFactory.create(GameObjectType::LIGHT_OBJECT, i, j);
                break;
            case 2:
                mapObjects[i][j] = gameObjectFactory.create(GameObjectType::HEAVY_OBJECT, i, j);
                break;
            case 3:
                mapObjects[i][j] = gameObjectFactory.create(GameObjectType::BORDER_OBJECT, i, j);
                break;

            }
        }
    }



    // инициализация главного героя
    player = gameObjectFactory.create(GameObjectType::PLAYER, 1, 1);

    for (int row = 0; row < 21; row++)
        delete[] matrix[row];
    delete[] matrix;
}
