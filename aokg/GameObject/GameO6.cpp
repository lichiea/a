#include"GameObject.h"

#include"GameObject.h"

// конструктор
GameObject::GameObject() { this->setPosition({ 0,0 }); }

// установка используемого графического объекта
// происходит копирование переданного объекта для последующего использования
void GameObject::setGraphicObject(const GraphicObject& graphicObjectk) {
    this->graphicObject = graphicObjectk; 
    this->graphicObject.setPosition({ this->position.x-10,0,this->position.y-10 });
};

// установка логических координат (два перегруженных метода для удобства)
void  GameObject::setPosition(int x, int y) { 
    ivec2 p(x, y); 
    this->position = p; 
};
void  GameObject::setPosition(ivec2 positionk) { this->position = positionk; };

// получение текущих логических координат
ivec2  GameObject::getPosition() { return position; };

// вывод игрового объекта на экран
void  GameObject::draw(void) {
    
        //graphicObject->setPosition(vec3(position.x - 10, 0, position.y - 10));
        this->graphicObject.draw();
    
};
