#include"GameObject.h"

// конструктор
GameObject::GameObject() {};

// установка используемого графического объекта
// происходит копирование переданного объекта для последующего использования
void GameObject::setGraphicObject(const GraphicObject& graphicObject) {};

// установка логических координат (два перегруженных метода для удобства)
void  GameObject::setPosition(int x, int y) {};
void  GameObject::setPosition(ivec2 position) {};

// получение текущих логических координат
ivec2  GameObject::getPosition() { return position; };

// вывод игрового объекта на экран
void  GameObject::draw(void) {};
