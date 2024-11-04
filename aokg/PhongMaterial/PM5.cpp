#include "PhongMaterial.h"

PhongMaterial::PhongMaterial() {};
PhongMaterial::~PhongMaterial() {};

void PhongMaterial::setAmbient(vec4 color) { ambient = color; }
void PhongMaterial::setDiffuse(vec4 color) { diffuse = color; }
void PhongMaterial::setSpecular(vec4 color) { specular = color; }
void PhongMaterial::setEmission(vec4 color) { emission = color; }
void PhongMaterial::setShininess(float p) { shininess = p; }

vec4 PhongMaterial::getAmbient() {return ambient; }
vec4 PhongMaterial::getDiffuse() {return diffuse; }
vec4 PhongMaterial::getSpecular() {return specular; }
vec4 PhongMaterial::getEmission() {return emission; }
float PhongMaterial::getShininess() {/* cout << shininess<<" "; */return shininess; }

void PhongMaterial::load(string filename) {
    ifstream vvod;

    vvod.open(filename);
    if (!vvod.is_open()) {
        cout << "ошибка";
    }
    else {
        string par;
        while (!vvod.eof()) {
            vvod >> par;
            if (par == "diffuse:") {
                vec4 temp;
                vvod >> par; temp.x = stof(par);
                vvod >> par; temp.y = stof(par);
                vvod >> par; temp.z = stof(par);
                vvod >> par; temp.w = stof(par);
                setDiffuse(temp);
            }
            if (par == "ambient:") {
                vec4 temp;
                vvod >> par; temp.x = stof(par);
                vvod >> par; temp.y = stof(par);
                vvod >> par; temp.z = stof(par);
                vvod >> par; temp.w = stof(par);
                setAmbient(temp);
            }
            if (par == "specular:") {
                vec4 temp;
                vvod >> par; temp.x = stof(par);
                vvod >> par; temp.y = stof(par);
                vvod >> par; temp.z = stof(par);
                vvod >> par; temp.w = stof(par);
                setSpecular(temp);
            }
            if (par == "emission:") {
                vec4 temp;
                vvod >> par; temp.x = stof(par);
                vvod >> par; temp.y = stof(par);
                vvod >> par; temp.z = stof(par);
                vvod >> par; temp.w = stof(par);
                setEmission(temp);
            }
            if (par == "shininess:") {
                vvod >> par;
                setShininess(stof(par));
            }
        }
    }
    vvod.close();
}
// установка всех параметров материала
void PhongMaterial::apply(){
    GLfloat dif[] = { 1.0,0.0,0.0,1.0 };
    GLfloat sp[] = { 0.0,0.0,0.0,1.0 };
    GLfloat am[] = { 0.2,0.0,0.0,1.0 };
    GLfloat em[] = { 0.0,0.0,0.0,1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, am); // Амбиентный цвет - серый
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif); // Диффузный цвет - белый
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sp); // Спекулярный цвет - белый
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, em); // 
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 64);
}
