#include <stdio.h>
#include <string>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<fstream>
#include<iostream>

using namespace glm;
using namespace std;


// КЛАСС ДЛЯ РАБОТЫ С МАТЕРИАЛОМ
class PhongMaterial
{
public:
	// конструктор по умолчанию
	PhongMaterial();
	// задание параметров материала
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);
	void setEmission(vec4 color);
	void setShininess(float p);
	vec4 getAmbient();
	vec4 getDiffuse();
	vec4 getSpecular();
	vec4 getEmission();
	float getShininess();
	// загрузка параметров материала из внешнего текстового файла
	void load(string filename);
	// установка всех параметров материала
	void apply();
	~PhongMaterial();
private:
	// фоновая составляющая
	vec4 ambient;
	// диффузная составляющая
	vec4 diffuse;
	// зеркальная составляющая
	vec4 specular;
	// самосвечение
	vec4 emission;
	// степень отполированности
	float shininess;
};
