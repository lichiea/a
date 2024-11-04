#include "PhongMaterial.h"

using namespace std;
PhongMaterial::PhongMaterial() {};
PhongMaterial::~PhongMaterial() {};

void PhongMaterial::setAmbient(vec4 color) {ambient = color; }
void PhongMaterial::setDiffuse(vec4 color) { diffuse = color; }
void PhongMaterial::setSpecular(vec4 color) { specular = color; }
void PhongMaterial::setEmission(vec4 color) { emission = color; }
void PhongMaterial::setShininess(float p) {shininess = p; }

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
                cout << par;
                vec4 temp{0.0,0.0,0.0,0.0};
                vvod >> par; temp.x = stod(par); cout << temp.x << " ";
                vvod >> par; temp.y = stod(par); cout << temp.y << " ";
                vvod >> par; temp.z = stod(par); cout <<  temp.z << " ";
                vvod >> par; temp.w = stod(par); cout << temp.w << " "<<endl;
                setDiffuse(temp);
            }
            if (par == "ambient:") {
                cout << par;
                vec4 temp;
                vvod >> par; temp.x = stod(par); cout << temp.x << " ";
                vvod >> par; temp.y = stod(par); cout << temp.y << " ";
                vvod >> par; temp.z = stod(par); cout << temp.z << " ";
                vvod >> par; temp.w = stod(par); cout << temp.w << " "<<endl;
                setAmbient(temp);
            }
            if (par == "specular:") {
                vec4 temp;
                vvod >> par; temp.x = stod(par);
                vvod >> par; temp.y = stod(par);
                vvod >> par; temp.z = stod(par);
                vvod >> par; temp.w = stod(par);
                setSpecular(temp);
            }
            if (par == "emission:") {
                vec4 temp;
                vvod >> par; temp.x = stod(par);
                vvod >> par; temp.y = stod(par);
                vvod >> par; temp.z = stod(par);
                vvod >> par; temp.w = stod(par);
                setEmission(temp);
            }
            if (par == "shininess:") {
                vvod >> par;
                setShininess(stod(par));
            }
        }
    }
    cout << endl;
    vvod.close();
}
// установка всех параметров материала
void PhongMaterial::apply(){

    glMaterialfv(GL_FRONT, GL_AMBIENT, &ambient[0]); //
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuse[0]); //
    glMaterialfv(GL_FRONT, GL_SPECULAR, &specular[0]); 
    glMaterialfv(GL_FRONT, GL_EMISSION, &emission[0]); // 
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}
