#include"GameObjectFactory.h"
using namespace glm;
using namespace std;
using namespace rapidjson;

// инициализация фабрики (загрузка мешей и установка параметров материала)
bool GameObjectFactory::init(std::string filename) {
	// открываем файл с заданным именем и проверяем, удалось ли его открыть
	ifstream file(filename);
	if (!file){
		cerr << "\n Не уадется найти файл  " << filename;
		return false;
	}
	IStreamWrapper buffer(file);
	Document doc;
	doc.ParseStream(buffer);
	file.close();
	if (doc.GetParseError() != 0){
		cerr << "неверный формат файла\n" << doc.GetParseError() << endl;
		return false;
	}

	// Функция для создания материала из JSON
	auto createMaterial = [](const Value& materialNode) -> shared_ptr<PhongMaterial> {
		glm::vec4 diffuse = glm::vec4(materialNode["diffuse"].GetArray()[0].GetFloat(),
			materialNode["diffuse"].GetArray()[1].GetFloat(),
			materialNode["diffuse"].GetArray()[2].GetFloat(),
			materialNode["diffuse"].GetArray()[3].GetFloat());

		glm::vec4 ambient = glm::vec4(materialNode["ambient"].GetArray()[0].GetFloat(),
			materialNode["ambient"].GetArray()[1].GetFloat(),
			materialNode["ambient"].GetArray()[2].GetFloat(),
			materialNode["ambient"].GetArray()[3].GetFloat());

		glm::vec4 specular = glm::vec4(materialNode["specular"].GetArray()[0].GetFloat(),
			materialNode["specular"].GetArray()[1].GetFloat(),
			materialNode["specular"].GetArray()[2].GetFloat(),
			materialNode["specular"].GetArray()[3].GetFloat());

		glm::vec4 emission = glm::vec4(materialNode["emission"].GetArray()[0].GetFloat(),
			materialNode["emission"].GetArray()[1].GetFloat(),
			materialNode["emission"].GetArray()[2].GetFloat(),
			materialNode["emission"].GetArray()[3].GetFloat());

		float shininess = materialNode["shininess"].GetFloat();

		return make_shared<PhongMaterial>();
		};

    // Загружаем данные для каждого типа объекта
    if (doc.HasMember("LightObject")) {
        auto& obj = doc["LightObject"];
        string meshPath = obj["mesh"].GetString();
        shared_ptr<Mesh> mesh = make_shared<Mesh>(); // Создание меша
        shared_ptr<PhongMaterial> material = createMaterial(obj["material"]);

        mes[GameObjectType::LIGHT_OBJECT] = mesh;
        mat[GameObjectType::LIGHT_OBJECT] = material;
    }

    if (doc.HasMember("HeavyObject")) {
        auto& obj = doc["HeavyObject"];
        string meshPath = obj["mesh"].GetString();
        shared_ptr<Mesh> mesh = make_shared<Mesh>(); // Создание меша
        shared_ptr<PhongMaterial> material = createMaterial(obj["material"]);

        mes[GameObjectType::HEAVY_OBJECT] = mesh;
        mat[GameObjectType::HEAVY_OBJECT] = material;
    }

    if (doc.HasMember("BorderObject")) {
        auto& obj = doc["BorderObject"];
        string meshPath = obj["mesh"].GetString();
        shared_ptr<Mesh> mesh = make_shared<Mesh>(); // Создание меша
        shared_ptr<PhongMaterial> material = createMaterial(obj["material"]);

        mes[GameObjectType::BORDER_OBJECT] = mesh;
        mat[GameObjectType::BORDER_OBJECT] = material;
    }

    if (doc.HasMember("Player")) {
        auto& obj = doc["Player"];
        string meshPath = obj["mesh"].GetString();
        shared_ptr<Mesh> mesh = make_shared<Mesh>(); // Создание меша
		mesh->load(meshPath);
        shared_ptr<PhongMaterial> material = createMaterial(obj["material"]);

        mes[GameObjectType::PLAYER] = mesh;
        mat[GameObjectType::PLAYER] = material;
    }

    if (doc.HasMember("Bomb")) {
        auto& obj = doc["Bomb"];
        string meshPath = obj["mesh"].GetString();
        shared_ptr<Mesh> mesh = make_shared<Mesh>(); // Создание меша
        shared_ptr<PhongMaterial> material = createMaterial(obj["material"]);

        mes[GameObjectType::BOMB] = mesh;
        mat[GameObjectType::BOMB] = material;
    }

    if (doc.HasMember("Monster")) {
        auto& obj = doc["Monster"];
        string meshPath = obj["mesh"].GetString();
        shared_ptr<Mesh> mesh = make_shared<Mesh>(); // Создание меша
        shared_ptr<PhongMaterial> material = createMaterial(obj["material"]);

        mes[GameObjectType::MONSTER] = mesh;
        mat[GameObjectType::MONSTER] = material;
    }

    return true;

}



shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, int x, int y) {
	shared_ptr<GameObject> a = make_shared<GameObject>();
	GraphicObject b;
	auto fi1 = mes.find(type);
	auto fi2 = mat.find(type);
	// проверяем, удалось ли найти элемент
	if (fi1 != mes.end()) {
		b.setMesh(fi1->second);
		cout << "a!";
	}
	else {};
	if (fi2 != mat.end()) {
		b.setMaterial(fi2->second);
	}
	else {};
	a->setPosition(x, y);
	a->setGraphicObject(b);
	return a;
}
