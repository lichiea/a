#include"GameObjectFactory.h"
using namespace glm;
using namespace std;
// инициализация фабрики (загрузка мешей и установка параметров материала)
bool GameObjectFactory::init(std::string filename) {
	// открываем файл с заданным именем и проверяем, удалось ли его открыть
	ifstream f(filename);
	if (!f.is_open()) {
		cout << "Не уадется найти файл " << filename << endl;
		return false;
	}
	// загружаем весь исходный текст (до разделителя - нулевого символа)
	cout << "парсим файл " << filename << ":\n";
	string jsonString;
	getline(f, jsonString, static_cast<char>(0));
	f.close();
	// выводим считанную строку для отладки
	cout << jsonString << endl;
	// парсим - если ошибка, то выходим
	Document document;
	document.Parse(jsonString.c_str());
	if (document.GetParseError() != 0) {
		cout << "неверный формат файла\n";
		return false;
	}

}



shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, int x, int y) {
	shared_ptr<GameObject> a;
	return a;
}