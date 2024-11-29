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
void GameObject::simulate(float sec) {
    if (this == nullptr) { return; }
    if (this->sost == MoveDirection::STOP) { return; }
    else {
        ivec2 pos2s = getPosition();
        vec3 posob = this->graphicObject.getPosition();
        
            switch (this->sost) {
            case MoveDirection::LEFT:
                posob.z += (1 - this->progress) / 20;

                cout << "(" << pos2s.x << "  " << pos2s.y << ")";
                this->graphicObject.setPosition({ posob.x,0,posob.z });
                this->progress += this->speed * sec;
                cout << this->progress << "   ";
                if (this->progress > 1) {
                    pos2s.y += 1;
                    this->progress = 1;
                    this->setPosition(pos2s.x, pos2s.y);
                    cout << "(" << pos2s.x << "  " << pos2s.y << ")";
                    this->graphicObject.setPosition({ this->position.x - 10,0,this->position.y - 10 });
                    this->sost = MoveDirection::STOP;
                    return;
                }
                cout << endl;
                break;
            case MoveDirection::RIGHT:
                posob.z -= (1 - this->progress) / 20;


                cout << "(" << pos2s.x << "  " << pos2s.y << ")";
                this->graphicObject.setPosition({ posob.x,0,posob.z });
                this->progress += this->speed * sec;
                cout << this->progress << "   ";
                if (this->progress > 1) {
                    pos2s.y -= 1;
                    this->progress = 1;
                    this->setPosition(pos2s.x, pos2s.y);
                    cout << "(" << pos2s.x << "  " << pos2s.y << ")";
                    this->graphicObject.setPosition({ this->position.x - 10,0,this->position.y - 10 });
                    this->sost = MoveDirection::STOP;
                    return;
                }
                cout << endl;
                break;
            case MoveDirection::UP:
                posob.x -= (1 - this->progress) / 20;
                cout << "(" << pos2s.x << "  " << pos2s.y << ")";
                this->graphicObject.setPosition({ posob.x,0,posob.z });
                this->progress += this->speed * sec;
                cout << this->progress << "   ";
                if (this->progress > 1) {
                    pos2s.x -= 1;
                    this->progress = 1;
                    this->setPosition(pos2s.x, pos2s.y);

                    cout << "(" << pos2s.x << "  " << pos2s.y << ")";
                    this->graphicObject.setPosition({ this->position.x - 10,0,this->position.y - 10 });
                    this->sost = MoveDirection::STOP;
                    return;
                }
                cout << endl;
                break;
            case MoveDirection::DOWN:
                this->progress += this->speed * sec;
                posob.x += (1- this->progress)/20;

                cout << "(" << pos2s.x << "  " << pos2s.y << ")";
                this->graphicObject.setPosition({ posob.x,0,posob.z});

                cout << this->progress << "   ";
                if (this->progress >1) {
                    pos2s.x += 1;
                    this->progress = 1;
                    this->setPosition(pos2s.x, pos2s.y);
                    cout << "(" << pos2s.x << "  " << pos2s.y << ")";
                    this->graphicObject.setPosition({ this->position.x - 10,0,this->position.y - 10 });
                    this->sost = MoveDirection::STOP;
                    return;
                }
                cout << endl;
                break;
            default:
                break;
            }
            //this->setPosition(pos2s.x, pos2s.y);
            //cout << "(" << pos2s.x << "  " << pos2s.y << ")";
            //this->graphicObject.setPosition({ this->position.x - 10,0,this->position.y - 10 });
            //this->progress += this->speed * sec;
            //cout << this->progress << "   ";
        
        //if (this->progress > 1) {
        //    this->progress = 1;
        //    this->setPosition(pos2s.x, pos2s.y);
        //    this->graphicObject.setPosition({ this->position.x - 10,0,this->position.y - 10 });
        //    this->sost = MoveDirection::STOP;
        //    return;
        //}
    }
}
