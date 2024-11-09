#include"GameObject.h"

// конструктор
GameObject::GameObject() {};

// установка используемого графического объекта
// происходит копирование переданного объекта для последующего использования
void GameObject::setGraphicObject(shared_ptr<GraphicObject> graphicObjectk) { this->graphicObject = graphicObjectk; };

// установка логических координат (два перегруженных метода для удобства)
void  GameObject::setPosition(int x, int y) { ivec2 p(x, y); this->position = p; };
void  GameObject::setPosition(ivec2 positionk) { this->position = positionk; };

// получение текущих логических координат
ivec2  GameObject::getPosition() { return position; };

// вывод игрового объекта на экран
void  GameObject::draw(void) {
    if (graphicObject) {
        graphicObject->setPosition(vec3(position.x, 0, position.y));
        graphicObject->draw();
    }
};
