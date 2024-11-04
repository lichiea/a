#pragma once
#include "Data.h"
#include "Light.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <functional>
#include <string>
#include <iostream>
using namespace std;
using namespace glm;

void display(void);
void processInput(float);
void getFPS();
void reshape(int w, int h);
void setProjection(int width, int height);
//перепутала с пятой, в cpp файле всё в норме 
