#include <windows.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GraphicObject.h"
#include<vector>

using namespace glm;
using namespace std;

vector<GraphicObject> graphicObjects;

// функция, вызываемая при изменении размеров окна
void reshape(int w, int h){
    // установить новую область просмотра, равную всей области окна
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    // установить матрицу проекции с правильным аспектом
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void display(void){
    // отчищаем буфер цвета и буфер глубины
    glClearColor(0.00, 0.00, 0.00, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // включаем тест глубины
    glEnable(GL_DEPTH_TEST);
    // устанавливаем камеру
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10, 15, 17.5, 0, 0, 0, 0, 1, 0);
    // выводим все графические объекты
    for (auto& go : graphicObjects) {
        go.draw();
    }
    // смена переднего и заднего буферов
    glutSwapBuffers();
};

// функция вызывается каждые 20 мс
void simulation(int value){
    // устанавливаем признак того, что окно нуждается в перерисовке
    glutPostRedisplay();
    // эта же функция будет вызвана еще раз через 20 мс
    glutTimerFunc(20, simulation, 0);
};

// Функция обработки нажатия клавиш
void keyboardFunc(unsigned char key, int x, int y){
    printf("Key code is %i\n", key);
};

void main(int argc, char** argv){
    setlocale(LC_ALL, "ru");
    // инициализация библиотеки GLUT
    glutInit(&argc, argv);
    // инициализация дисплея (формат вывода)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    // СОЗДАНИЕ ОКНА:
    // 1. устанавливаем верхний левый угол окна
    glutInitWindowPosition(200, 200);
    // 2. устанавливаем размер окна
    glutInitWindowSize(800, 600);
    // 3. создаем окно
    glutCreateWindow("Laba_03");
    // УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
    // устанавливаем функцию, которая будет вызываться для перерисовки окна
    glutDisplayFunc(display);
    // устанавливаем функцию, которая будет вызываться при изменении размеров окна
    glutReshapeFunc(reshape);
    // устанавливаем функцию, которая будет вызвана через 20 мс
    glutTimerFunc(20, simulation, 0);
    // устанавливаем функцию, которая будет вызываться при нажатии на клавишу
    glutKeyboardFunc(keyboardFunc);
    // ИНИЦИАЛИЗАЦИЯ ДАННЫХ, НЕОБХОДИМЫХ ДЛЯ РАБОТЫ ПРОГРАММЫ:
    // инициализация графических объектов
    GraphicObject tempGraphicObject;
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
