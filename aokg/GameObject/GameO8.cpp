#include"GameObject.h"

// конструктор
GameObject::GameObject() {}

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
    //this->graphicObject.setPosition({ x - 10,0,y - 10 });
};
void  GameObject::setPosition(ivec2 positionk) { 
    this->position = positionk; 
    //this->graphicObject.setPosition({ positionk.x - 10,0,positionk.y - 10 });
};

void GameObject::setPositionCube(int x, int y) {
    ivec2 p(x, y);
    this->position = p;
    this->graphicObject.setPosition({ x - 10,0,y - 10 });

}

// получение текущих логических координат
ivec2  GameObject::getPosition() { return this->position; };
MoveDirection GameObject::getSost() { return this->sost; };
void GameObject::setType(GameObjectType got) {
    this->tip = got;
};
GameObjectType GameObject::getType() { 
    if (this!=nullptr) return this->tip; 
};
// вывод игрового объекта на экран
void  GameObject::draw(void) {
        this->graphicObject.draw();
};

void GameObject::move(MoveDirection direction){
    //if (this->isMoving() == false) { return; }
    //else {
        this->speed = 0.3;
        this->sost = direction;
        this->progress = 0;
    //}
}
// проверка на то, что объект в настоящий момент движется
bool GameObject::isMoving() {
    if (this->sost == MoveDirection::STOP) return false;
    else return true;
}
// симуляция игрового объекта (плавное перемещение объекта)
// метод вызывается непрерывно в функции simulation
void GameObject::simulate(const ivec2& targetPos, float deltaTime) {
    if (this->sost == MoveDirection::STOP) return;

    vec3 currentPos = this->graphicObject.getPosition();
    vec3 targetPos3D = { (float)targetPos.x -10, 0, (float)targetPos.y- 10 };

    float distance = glm::distance(currentPos, targetPos3D);
    float moveDistanceThisFrame = this->speed * deltaTime;

    float lerpValue = std::min(1.0f, moveDistanceThisFrame / distance);
    vec3 newPos = glm::mix(currentPos, targetPos3D, lerpValue);
    this->graphicObject.setPosition(newPos);

    if (distance <= moveDistanceThisFrame) {
        this->graphicObject.setPosition(targetPos3D);
        this->sost = MoveDirection::STOP;
        this->setPosition(targetPos.x, targetPos.y);
    }
}
