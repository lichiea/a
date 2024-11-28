#pragma once
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include "GL1/glew.h"
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <functional>
#include "Data.h"
#include"Camera.h"
#include<string>
using namespace glm;

// Установка и получение позиции объекта
void simulation();
float getSimulationTime();
void initializeTiming();
void gameObjectSimulation(float);
void movePlayer(float);
