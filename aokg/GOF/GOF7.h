#pragma once
#include<vector>
#include<memory>
#include "Mesh.h"
#include "GameObject.h"
#include <rapidjson/document.h>
#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include<iostream>
#include<map>
#include<string>
// указываем используемые пространства имен
using namespace rapidjson;
using namespace glm;
using namespace std;


// ОПРЕДЕЛЕНИЕ ТИПОВ ИГРОВЫХ ОБЪЕКТОВ
enum class GameObjectType {
	LIGHT_OBJECT, // легкий игровой объект
	HEAVY_OBJECT, // тяжелый игровой объект
	BORDER_OBJECT, // граничный игровой объект
	PLAYER, // игровой объект для представления игрока
	BOMB, // игровой объект для представления бомбы
	MONSTER // игровой объект для представления монстров
};

// КЛАСС ДЛЯ СОЗДАНИЯ ИГРОВЫХ ОБЪЕКТОВ
class GameObjectFactory
{
public:
	GameObjectFactory() {};
	// инициализация фабрики (загрузка мешей и установка параметров материала)
	bool init(std::string filename);
	// создание нового объекта заданного типа
	shared_ptr<GameObject> create(GameObjectType type, int x, int y);

	vec4 extractVec4(const Value& node);

	shared_ptr<PhongMaterial> createMaterial(const Value& materialNode);
private:
	// меши для каждого типа объекта
	vector<shared_ptr<Mesh>> Meshes;
	// материалы для каждого типа объекта
	vector<shared_ptr<PhongMaterial>> Materials;
	map<GameObjectType, shared_ptr<Mesh>> mes;
	map<GameObjectType, shared_ptr<PhongMaterial>> mat;

};
