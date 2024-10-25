#include <windows.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GraphicObject.h"
#include "Data.h"
#include "Display.h"
#include "Simulation.h"
#include "Camera.h"
#include<vector>
#include<string>

using namespace glm;
using namespace std;

vector<GraphicObject> graphicObjects;
vec3 p(10,15,17.5);

// функция, вызываемая при изменении размеров окна
void reshape(int w, int h) {
    // установить новую область просмотра, равную всей области окна
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    // установить матрицу проекции с правильным аспектом
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};


Camera cam;

LARGE_INTEGER frequency;
LARGE_INTEGER lastTime;
LARGE_INTEGER currentTime;
int frameCount = 0;
void getSimulationTime() {
    frameCount++;

    // Обновление счетчика кадров в секунду
    QueryPerformanceCounter(&currentTime);
    if (currentTime.QuadPart - lastTime.QuadPart >= frequency.QuadPart) {
        float fps = (float)frameCount / ((double)(currentTime.QuadPart - lastTime.QuadPart) / frequency.QuadPart);
        string title = "FPS: " + to_string(fps);
        glutSetWindowTitle(title.c_str());
        frameCount = 0;
        lastTime = currentTime;
    }
}

void getFPS() {
    QueryPerformanceFrequency(&frequency);
}

// Инициализация счетчика производительности

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void display(void) {
    // отчищаем буфер цвета и буфер глубины
    glClearColor(0.00, 0.00, 0.00, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // включаем тест глубины
    glEnable(GL_DEPTH_TEST);
    // устанавливаем камеру
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    cam.apply();

    // выводим все графические объекты
    for (auto& go : graphicObjects) {
        go.draw();
    }


    getSimulationTime();
    // смена переднего и заднего буферов
    glutSwapBuffers();
};


// Функция обработки нажатия клавиш
void keyboardFunc(unsigned char key, int x, int y) {
    
        printf("Key code is %i\n", key);
        // для провекри класса камеры вызываем методы передвижения
        switch (static_cast<char>(key)) {
        case 'w':
            cam.rotateUpDown(1.35);
            break;
        case 's':
            cam.rotateUpDown(-1.35);
            break;
        case 'a':
            cam.rotateLeftRight(1.35);
            break;
        case 'd':
            cam.rotateLeftRight(-1.35);
            break;
        case '+':
            cam.zoomInOut(1.35);
            break;
        case '-':
            cam.zoomInOut(-1.35);
            break;
        }
    
};

void main(int argc, char** argv) {

    getFPS();

    setlocale(LC_ALL, "ru");
    // инициализация библиотеки GLUT
    glutInit(&argc, argv);
    // инициализация дисплея (формат вывода)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    // СОЗДАНИЕ ОКНА:
    // 1. устанавливаем верхний левый угол окна
    glutInitWindowPosition(100, 100);
    // 2. устанавливаем размер окна
    glutInitWindowSize(800, 600);
    // 3. создаем окно
    glutCreateWindow("Laba_04");
    // УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
    // устанавливаем функцию, которая будет вызываться для перерисовки окна
    glutDisplayFunc(display);
    // устанавливаем функцию, которая будет вызываться при изменении размеров окна
    glutReshapeFunc(reshape);

    glutIdleFunc(simulation);
    // устанавливаем функцию, которая будет вызываться при нажатии на клавишу
    glutKeyboardFunc(keyboardFunc);
    // ИНИЦИАЛИЗАЦИЯ ДАННЫХ, НЕОБХОДИМЫХ ДЛЯ РАБОТЫ ПРОГРАММЫ:
    // инициализация графических объектов
    GraphicObject tempGraphicObject;

    cam.setPosition(vec3(10, 15, 17.5));

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
    // основной цикл обработки сообщений ОС
    glutMainLoop();
};
