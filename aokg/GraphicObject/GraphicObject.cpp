#include "GraphicObject.h"

GraphicObject::GraphicObject() {};

void GraphicObject::setPosition(vec3 position_temp){
	position = position_temp;
	recalculateModelMatrix();
};

vec3 GraphicObject::getPosition(){return position;}

void GraphicObject::setAngle(float grad) {
	angle = grad;
	recalculateModelMatrix();
};

float GraphicObject::getAngle(){return angle;}

void GraphicObject::setСolor(vec3 color_temp) {color = color_temp;};

vec3 GraphicObject::getColor() {return color;}
// расчет матрицы modelMatrix на основе position и angle
void GraphicObject::recalculateModelMatrix(){
	mat4 model=mat4(1.0);
	// Перевод
	model = translate(model, getPosition());
	
	// Вращение вокруг
	model = rotate(model, radians(getAngle()),vec3(0.0,1.0,0.0));

	// Сохранение матрицы в массив GLfloat
	for (int i = 0; i < 16; ++i) {
		float value = model[i / 4][i % 4];
		if (i < 12) modelMatrix[i] = (value >= 0.5) ? 1.0 : (value <= -0.5) ? -1.0 : 0.0;
		else {
			modelMatrix[i] = (value >= 4.5) ? 5.0 : (value <= -4.5) ? -5.0 : 0.0;
		}
		modelMatrix[15] = 1.0;
	}
}
// вывести объект
void GraphicObject::draw(){
	vec3 c = getColor();
	glColor3f(c.r, c.g, c.b);
	glPushMatrix();
	glMultMatrixf(modelMatrix);
	glutWireTeapot(1.0);
	glPopMatrix();
}
