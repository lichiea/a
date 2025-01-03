#include "Mesh.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

// конструктор
Mesh::Mesh() {};
// загрузка меша из файла с указанным именем
void Mesh::load(std::string filename) {
    vector <string> strFPoints;
    ifstream vvod;
    // вектор для хранения геометрических координат
    vector<vec3> v;
    // вектор для хранения нормалей
    vector<vec3> n;
    // вектор для хранения текстурных координат
    vector<vec2> t;
    // вектор для хранения индексов атрибутов, для построения вершин
    vector<ivec3> fPoints;

    vvod.open(filename);
    if (!vvod.is_open()) {
        cout << "ошибка";
    }
    else {
        string par;
        while (!vvod.eof()) {
            vvod >> par;
            if (par == "v") {
                vec3 temp{ 0.0,0.0,0.0};
                vvod >> par; temp.x = stod(par); 
                vvod >> par; temp.y = stod(par);
                vvod >> par; temp.z = stod(par);
                v.push_back(temp);

            }
            if (par == "vn") {
                vec3 temp;
                vvod >> par; temp.x = stod(par);
                vvod >> par; temp.y = stod(par);
                vvod >> par; temp.z = stod(par);
                n.push_back(temp);

            }
            if (par == "vt") {
                vec2 temp;
                vvod >> par; temp.x = stod(par);
                vvod >> par; temp.y = stod(par);
                t.push_back(temp);
      
            }
            if (par == "f") {
                ivec3 temp;
                for (int i=0; i<3;i++){ 
                    int c = 0;
                    vvod >> par;
                    
                    strFPoints.push_back(par);
                    istringstream stream(par);  // Создаем поток из строки
                    int number;
                    char slash;  // Для считывания символа '/' после числа
                    // Пока в потоке есть данные
                    while (stream >> number) {
                        c += 1;
                        temp[c-1] = number;
                        // Пропускаем символ '/'
                        if (stream >> slash && slash != '/') {
                            std::cerr << "Ожидался символ '/', но найден: " << slash << std::endl;
                            break;  // Выход из цикла, если символ не '/'
                        }
                    }
                    fPoints.push_back(temp);
                }
            }
            else{}
        }
        form_v(v,n,t,fPoints,strFPoints);
    }

    vvod.close();

};
// вывод меша (передача всех вершин в OpenGL)
void Mesh::draw() {
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &vertices[0].coord[0]);
    glNormalPointer(GL_FLOAT, sizeof(Vertex), &vertices[0].normal[0]);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &vertices[0].texCoord[0]);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices[0]);
    
};

void Mesh::form_v(vector<vec3> v, vector<vec3> n, vector<vec2> t, vector<ivec3> fPoints, vector<string>str) {
    map <string, int> forms;
    int a = 0;
    for (int i = 0; i < str.size(); ++i) {
        pair<string, int> sr;
        sr.first = str[i];
        sr.second = a;
        auto fi = forms.find(str[i]);
        // проверяем, удалось ли найти элемент
        if (fi != forms.end()) {
            GLuint gl = fi->second;
            indices.push_back(gl);
        }
        else {

            Vertex ver;
            for (int q = 0; q < 3; q++) {
                ver.coord[q] = v[fPoints[i][0] - 1][q];
                ver.normal[q] = n[fPoints[i][2] - 1][q];
            }
            for (int q = 0; q < 2; q++) {
                ver.texCoord[q] = t[fPoints[i][1] - 1][q];
            }
            GLuint gl = a;
            vertices.push_back(ver);
            indices.push_back(gl);
            forms.insert(sr);
            a++;
        };
 
    }

};
