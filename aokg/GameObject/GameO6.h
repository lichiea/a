#pragma once

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include "PhongMaterial.h"
#include<memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ОДНОГО ГРАФИЧЕСКОГО ОБЪЕКТА
class GraphicObject {
public:
    // Конструктор
    GraphicObject();
    // Установка и получение позиции объекта
    void setPosition(vec3 position_temp);
    vec3 getPosition();
    // Установка и получения угла поворота в градусах
    // поворот осуществляется в горизонтальной плоскости
    // вокруг оси Oy по часовой стрелке
    void setAngle(float grad);
    float getAngle();
    // Установка текущего цвета объекта
    void setСolor(vec3 color_temp);
    vec3 getColor();
    // Установка используемого материала
    void setMaterial(std::shared_ptr<PhongMaterial> material);
    shared_ptr<PhongMaterial>getMaterial();
    // Вывести объект
    void draw();
    ~GraphicObject() {};
private:
    // Позиция объекта в глобальной системе координат
    vec3 position;
    // Угол поворота в горизонтальной плоскости (в градусах)
    float angle;
    // Цвет модели
    vec3 color;
    // Матрица модели (расположение объекта) - чтоб не вычислять каждый раз
    GLfloat modelMatrix[16];
    std::shared_ptr<PhongMaterial> material;
private:
    // расчет матрицы modelMatrix на основе position и angle
    void recalculateModelMatrix();
};
