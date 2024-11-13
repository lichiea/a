#include "GraphicObject.h"

GraphicObject::GraphicObject():position(vec3(0.0,0.0,0.0)) {};

void GraphicObject::setPosition(vec3 position_temp) {
	if (this != nullptr) {
				this->position = position_temp;
		recalculateModelMatrix();
		}

	//cout << "(" << position.x << ", " << position.y << ", " << position.z << ")" << endl;
};

vec3 GraphicObject::getPosition() { //cout << "(" << position.x << ", " << position.y << ", " << position.z << ")" << endl; 
return this->position;  }

void GraphicObject::setAngle(float grad) {
	angle = grad;
	recalculateModelMatrix();
};
float GraphicObject::getAngle() { return angle; }

void GraphicObject::setСolor(vec3 color_temp) { color = color_temp; };
vec3 GraphicObject::getColor() { return color; }

void GraphicObject::setMaterial(shared_ptr<PhongMaterial> materialk) { material = materialk; };
shared_ptr<PhongMaterial> GraphicObject::getMaterial() { return material; };

// расчет матрицы modelMatrix на основе position
void GraphicObject::recalculateModelMatrix() {

	mat4 model = mat4(1.0);  // Единичная матрица
	model = translate(model, this->getPosition());  // Применяем сдвиг

	// Копируем матрицу преобразования в массив modelMatrix
	for (int i = 0; i < 16; ++i) {
		//if (i % 4 == 0)cout << endl;
		modelMatrix[i] = model[i / 4][i % 4];
		//cout << modelMatrix[i]<<" ";

	}
	//cout << endl;

}
// вывести объект
void GraphicObject::draw() {

	glColor3f(this->color.r, this->color.g, this->color.b);

	if (this->material != nullptr) {
		this->material->apply();
	}

	glPushMatrix();
	glMultMatrixf(modelMatrix);

	if (this->mesh != nullptr) {
		this->mesh->draw();
	}
	glPopMatrix();
}

void GraphicObject::setMesh(std::shared_ptr<Mesh> meshk) { mesh = meshk; }
shared_ptr<Mesh> GraphicObject::getMesh() { return mesh; }
