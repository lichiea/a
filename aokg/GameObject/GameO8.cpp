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

// получение текущих логических координат
ivec2  GameObject::getPosition() { return this->position; };

// вывод игрового объекта на экран
void  GameObject::draw(void) {
        this->graphicObject.draw();
};

void GameObject::move(MoveDirection direction){
    this->speed = 0.3;
    this->sost = direction;
    this->progress = 0;

}
// проверка на то, что объект в настоящий момент движется
bool GameObject::isMoving() {
    if (this->sost == MoveDirection::STOP) return false;
    else return true;
}
// симуляция игрового объекта (плавное перемещение объекта)
// метод вызывается непрерывно в функции simulation
void GameObject::simulate(float sec) {
    if (this->sost == MoveDirection::STOP) { return; }
    else {
        ivec2 pos2 = getPosition();
        this->progress +=  sec*1000;
        cout << sec<<"  ";
        if (this->progress > 1) {
            this->progress = 0;
            this->sost = MoveDirection::STOP;
            return;
        }

        ivec2 newPos = this->position;
        switch (sost) {
        case MoveDirection::LEFT:
            this->setPosition(this->getPosition().x, (this->getPosition().y + this->progress));
            this->graphicObject.setPosition({ this->position.x - 10,0,this->position.y - 10 });

            //sost = MoveDirection::STOP;
            break;
        case MoveDirection::RIGHT:
            this->setPosition(this->getPosition().x, (this->getPosition().y - 1));
            this->graphicObject.setPosition({ this->position.x - 10,0,this->position.y - 10 });
            sost = MoveDirection::STOP;
            break;
        case MoveDirection::UP:
             this->setPosition((this->getPosition().x - 1), this->getPosition().y);
            this->graphicObject.setPosition({ this->position.x - 10,0,this->position.y - 10 });
            sost = MoveDirection::STOP;
            break;
        case MoveDirection::DOWN:
            this->setPosition((this->getPosition().x + 1), this->getPosition().y);
            this->graphicObject.setPosition({ this->position.x- 10,0,this->position.y - 10 });
            sost = MoveDirection::STOP;
            break;
        default:
            //this->graphicObject.setPosition({ this->position.x - 10,0,this->position.y - 10 });
            //this->setPosition((this->getPosition().y - 1) * 0.3 * sec + 10, this->getPosition().y);
            break;
        }
    }
}
