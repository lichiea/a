#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

// КЛАСС ДЛЯ РАБОТЫ С ИСТОЧНИКОМ СВЕТА
class Light
{
public:
	// конструкторы
	Light();
	Light(vec3 position);
	Light(float x, float y, float z);
	// задание различных параметров источника света
	void setPosition(vec4 position);
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);
	// установка всех параметров источника света с заданным номером
	// данная функция должна вызываться после установки камеры,
	// т.к. здесь устанавливается позиция источника света
	void apply(GLenum LightNumber = GL_LIGHT0);
	~Light();
private:
	// позиция источника света
	vec4 position;
	// фоновая составляющая источника света
	vec4 ambient;
	// диффузная составляющая
	vec4 diffuse;
	// зеркальная составляющая
	vec4 specular;
};
