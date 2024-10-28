#include <windows.h>

#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<vector>

using namespace glm;

// используем пространство имен стандартной библиотеки
using namespace std;

void smena(double);
void gradient(double);

int i = 0;
int a = 0;
double k = 0;

vec3 white(1.0, 1.0, 1.0), blue(0.0, 0.0, 1.0), red(1.0, 0.0, 0.0), yellow(1.0, 1.0, 0.0), fiolet(0.5, 0.0, 1.0), grad(1.0, 1.0, 1.0),grad1(1.0, 1.0, 1.0),grad2(0.0, 0.0, 1.0);
vector<vec3> col = { white, blue, red, yellow, fiolet };


// функция, вызываемая при изменении размеров окна
void reshape(int w, int h)
{
    // установить новую область просмотра, равную всей области окна
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    // установить матрицу проекции с правильным аспектом
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void display(void)
{
    // отчищаем буфер цвета и буфер глубины
    glClearColor(0.22, 0.88, 0.11, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // включаем тест глубины
    glEnable(GL_DEPTH_TEST);

    // устанавливаем камеру
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 7.5, 0, 0, 0, 0, 1, 0);

    glColor3f(grad.r, grad.g, grad.b);
    glutWireTeapot(1.0);

    // смена переднего и заднего буферов
    glutSwapBuffers();
};

// функция вызывается каждые 20 мс
void simulation(int value) {
    // устанавливаем признак того, что окно нуждается в перерисовке
    glutPostRedisplay();
    // эта же функция будет вызвана еще раз через 20 мс
    glutTimerFunc(20, simulation, 0);
    smena(a);
 //   gradient(a);
};

vec3 temp(1.0, 1.0, 1.0);

void smena(double dop) {
    a++;
    if (dop > 50) {
        a = 0;
        i++;
        if (i > 4)i = 0;
        temp = col[i];
        cout << "смена цвета: " << i<<endl;
    }
    grad.r = temp.r;
    grad.g = temp.g;
    grad.b = temp.b;
}

void gradient(double dop) {
    a++;
    if (dop > 100) {
        a = 0;
        i++;
        if (i > 3)i = 0;
        grad1 = col[i];
        grad2 = col[i + 1];
        k = 0;
    }
    grad.r = k * (grad2.r - grad1.r) + grad1.r;
    grad.g = k * (grad2.g - grad1.g) + grad1.g;
    grad.b = k * (grad2.b - grad1.b) + grad1.b;
    k += 0.01;
}

// Функция обработки нажатия клавиш
void keyboardFunc(unsigned char key, int x, int y)
{
    printf("Key code is %i\n", key);
    i++;
    if (i == 5) i = 0;
};

void main(int argc, char** argv)
{
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
    glutCreateWindow("Laba_02");

    // УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
    // устанавливаем функцию, которая будет вызываться для перерисовки окна
    glutDisplayFunc(display);
    // устанавливаем функцию, которая будет вызываться при изменении размеров окна
    glutReshapeFunc(reshape);
    // устанавливаем функцию, которая будет вызвана через 20 мс
    glutTimerFunc(20, simulation, 0);
    // устанавливаем функцию, которая будет вызываться при нажатии на клавишу
    glutKeyboardFunc(keyboardFunc);

    // основной цикл обработки сообщений ОС
    glutMainLoop();
};
