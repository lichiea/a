#include <windows.h>
#include <iostream>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Display.h"
#include "Simulation.h"

using namespace glm;
using namespace std;


void main(int argc, char** argv) {
    setlocale(LC_ALL, "ru");
    // инициализация библиотеки GLUT
    glutInit(&argc, argv);
    // ИНИЦИАЛИЗАЦИЯ ДАННЫХ, НЕОБХОДИМЫХ ДЛЯ РАБОТЫ ПРОГРАММЫ:


    // инициализация дисплея (формат вывода)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    // СОЗДАНИЕ ОКНА:
    // 1. устанавливаем верхний левый угол окна
    glutInitWindowPosition(400, 10);
    // 2. устанавливаем размер окна
    glutInitWindowSize(800, 600);
    // 3. создаем окно
    glutCreateWindow("Laba_08");

    // ПОЛУЧЕНИЕ ИНФОРМАЦИИ ОБ OPENGL
    printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
    printf("GL_VERSION = %s\n\n", glGetString(GL_VERSION));

    // инициализация GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        printf("Error: %s\n", glewGetErrorString(err));
    }
    printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    // проверка поддержки расширения для работы с буфером VBO
    if (GLEW_ARB_vertex_buffer_object) {
        printf("VBO is supported");
    };

    // инициализация графических объектов
    initData();

    // УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
    // устанавливаем функцию, которая будет вызываться для перерисовки окна
    glutDisplayFunc(display);
    // устанавливаем функцию, которая будет вызываться при изменении размеров окна
    glutReshapeFunc(reshape);

    glutIdleFunc(simulation);
    // устанавливаем функцию, которая будет вызываться при нажатии на клавишу
    //glutKeyboardFunc(keyboardFunc);



    // основной цикл обработки сообщений ОС
    glutMainLoop();
};
