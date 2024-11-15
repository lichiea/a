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
#include "Light.h"
#include "PhongMaterial.h"
#include "Simulation.h"
#include "Camera.h"
#include <vector>
#include <string>

using namespace glm;
using namespace std;
//https://github.com/lpestl/Maze?tab=readme-ov-file#12-реализация-на-c

void main(int argc, char** argv) {
    setlocale(LC_ALL, "ru");
    // инициализация библиотеки GLUT
    glutInit(&argc, argv);
    // инициализация дисплея (формат вывода)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    // СОЗДАНИЕ ОКНА:
    // 1. устанавливаем верхний левый угол окна
    glutInitWindowPosition(400, 10);
    // 2. устанавливаем размер окна
    glutInitWindowSize(800, 600);
    // 3. создаем окно
    glutCreateWindow("Laba_06");
    // УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
    // устанавливаем функцию, которая будет вызываться для перерисовки окна
    glutDisplayFunc(display);
    // устанавливаем функцию, которая будет вызываться при изменении размеров окна
    glutReshapeFunc(reshape);

    glutIdleFunc(simulation);
    // устанавливаем функцию, которая будет вызываться при нажатии на клавишу
    //glutKeyboardFunc(keyboardFunc);
    // ИНИЦИАЛИЗАЦИЯ ДАННЫХ, НЕОБХОДИМЫХ ДЛЯ РАБОТЫ ПРОГРАММЫ:
    // инициализация графических объектов
    initData();
    // основной цикл обработки сообщений ОС
    glutMainLoop();
};
