#include"Simulation.h"

// Инициализация времени
void initializeTiming() {
    QueryPerformanceFrequency(&frequency); // Получаем частоту таймера
    QueryPerformanceCounter(&lastCounter);  // Получаем начальный отсчет
    QueryPerformanceCounter(&lastFPSCounter); // Получаем начальный отсчет для FPS
    frameCount = 0; // Инициализация счетчика кадров
}

// Функция для получения времени симуляции
float getSimulationTime() {
    LARGE_INTEGER currentCounter;
    QueryPerformanceCounter(&currentCounter); // Получаем текущий отсчет

    // Вычисляем время, прошедшее с последнего вызова
    float deltaTime = static_cast<float>(currentCounter.QuadPart - lastCounter.QuadPart) / frequency.QuadPart;

    // Обновляем последний отсчет
    lastCounter = currentCounter;

    return deltaTime; // Возвращаем прошедшее время
}

// Функция симуляции - вызывается максимально часто
void simulation() {
    // Определение времени симуляции
    simulationTime = getSimulationTime();

    gameObjectSimulation(simulationTime);
    //movePlayer(simulationTime);
 
    // Устанавливаем признак того, что окно нуждается в перерисовке
    glutPostRedisplay();
}


void gameObjectSimulation(float ttime) {
    ivec2 pos = player->getPosition();
    ivec2 poss = player->getPosition();
    MoveDirection s=player->getSost();
    if (s != MoveDirection::STOP) {
        switch (s) {
        case MoveDirection::LEFT:
            pos.y += 1;
            break;
        case MoveDirection::RIGHT:
            pos.y -= 1;
            break;
        case MoveDirection::UP:
            pos.x -= 1;
            break;
        case MoveDirection::DOWN:
            pos.x += 1;
            break;
        default:
            break;
        }
        if (passabilityMap[pos.x][pos.y] == 0) {
            movePlayer(ttime);
            cout << "a";
        }
        if (passabilityMap[pos.x][pos.y] == 1) {
            movePlayer(ttime);
            cout << "b";
        }
        else {
            cout << "c";
            //player->setPosition(poss);
            //player->move(MoveDirection::STOP); 
        }
    }
}
void movePlayer(float ttime) {
    player->simulate(simulationTime*50);
}
