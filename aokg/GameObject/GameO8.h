#pragma once
#include <windows.h>
#include <iostream>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <GL/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include "GraphicObject.h"

// класс-перечисление для указания направления перемещения
enum class MoveDirection { STOP, LEFT, RIGHT, UP, DOWN };
// ОПРЕДЕЛЕНИЕ ТИПОВ ИГРОВЫХ ОБЪЕКТОВ
enum class GameObjectType {
	LIGHT_OBJECT, // легкий игровой объект
	HEAVY_OBJECT, // тяжелый игровой объект
	BORDER_OBJECT, // граничный игровой объект
	PLAYER, // игровой объект для представления игрока
	BOMB, // игровой объект для представления бомбы
	MONSTER // игровой объект для представления монстров
};
// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ИГРОВОГО ОБЪЕКТА
class GameObject
{
public:
	// конструктор
	GameObject();
	// установка используемого графического объекта
	// происходит копирование переданного объекта для последующего использования
	void setGraphicObject(const GraphicObject& object);
	// установка логических координат (два перегруженных метода для удобства)
	void setPosition(int x, int y);
	void setPosition(ivec2 position);
	// получение текущих логических координат
	ivec2 getPosition();
	MoveDirection getSost();
	void setType(GameObjectType got);
	GameObjectType getType();
	// вывод игрового объекта на экран
	void draw(void);
	// начать движение в выбранном направлении с указанной скоростью
// скорость передвижения определяется количеством клеток в секунду
	void move(MoveDirection direction);
	// проверка на то, что объект в настоящий момент движется
	bool isMoving();
	// симуляция игрового объекта (плавное перемещение объекта)
	// метод вызывается непрерывно в функции simulation
	void simulate(float sec);
private:
	// логические координаты игрового объекта
	ivec2 position;
	// графический объект (для вывода на экран)
	GraphicObject graphicObject;
	// состояние объекта (заданное направление перемещения)
	MoveDirection sost;
	// прогресс в перемещении (от 0.0 до 1.0)
	float progress;
	// скорость перемещения
	float speed;
	GameObjectType tip;
};
