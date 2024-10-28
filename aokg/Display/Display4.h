#pragma once
#include "Data.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <functional>
#include <string>

using namespace glm;

void display(void);
void processInput(float);
void getFPS();
