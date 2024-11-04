#include "Light.h"

Light::Light() {};
Light::~Light() {};

void Light::setPosition(vec4 positionk) { position = positionk; }
void Light::setAmbient(vec4 color) { ambient = color; }
void Light::setDiffuse(vec4 color) { diffuse = color; }
void Light::setSpecular(vec4 color) { specular = color; }

void Light::apply(GLenum LightNumber) {
    // устанавливаем общую фоновую освещенность
    GLfloat globalAmbientColor[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat glmodel[] = { 0.0, 0.0, 0.0, 0.0 };
    GLfloat amb[] = { 0.4, 0.0, 0.0, 1.0 };
    GLfloat dif[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat spec[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat pos[] = { 20.0, 20.0, 15.0, 0.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);

    glEnable(LightNumber);
    glLightfv(LightNumber, GL_AMBIENT, amb);
    glLightfv(LightNumber, GL_DIFFUSE, dif);
    glLightfv(LightNumber, GL_SPECULAR, spec);
    glLightfv(LightNumber, GL_POSITION, pos);
}
