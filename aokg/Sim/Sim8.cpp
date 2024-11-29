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
    
    
    // Устанавливаем признак того, что окно нуждается в перерисовке
    glutPostRedisplay();
}


void gameObjectSimulation(float deltaTime) { // Use deltaTime instead of ttime
    MoveDirection s = player->getSost();
    if (s != MoveDirection::STOP) {
        ivec2 currentPos = player->getPosition();
        ivec2 targetPos = currentPos; // Target position

        switch (s) {
        case MoveDirection::LEFT:  targetPos.y++; break;
        case MoveDirection::RIGHT: targetPos.y--; break;
        case MoveDirection::UP:    targetPos.x--; break;
        case MoveDirection::DOWN:  targetPos.x++; break;
        }

        if (mapObjects[targetPos.x][targetPos.y] == nullptr) { // Check for empty space
            movePlayer(targetPos, deltaTime); // Pass target position and deltaTime
        }
        else if (mapObjects[targetPos.x][targetPos.y]->getType() == GameObjectType::LIGHT_OBJECT) {
            pushCube(targetPos, s, deltaTime); // Handle cube pushing
        }
    }
}


void movePlayer(const ivec2& targetPos, float deltaTime) {
    player->simulate(targetPos, deltaTime*10);
}

void pushCube(const ivec2& targetPos, MoveDirection dir, float deltaTime) {
    shared_ptr <GameObject> cube = mapObjects [targetPos.x][targetPos.y];
    ivec2 nextCubePos = targetPos;
    switch (dir) {
    case MoveDirection::LEFT: nextCubePos.y++; break;
    case MoveDirection::RIGHT: nextCubePos.y--; break;
    case MoveDirection::UP: nextCubePos.x--; break;
    case MoveDirection::DOWN: nextCubePos.x++; break;
    }

    if (mapObjects[nextCubePos.x][nextCubePos.y] == nullptr) {
        cube->setPositionCube(nextCubePos.x, nextCubePos.y);
        mapObjects[nextCubePos.x][nextCubePos.y] = cube; //Important, re-assign the cube in the map
        mapObjects[targetPos.x][targetPos.y] = nullptr;
        // Simulate the movement to a new location.  crucial!
        cube->simulate(nextCubePos, deltaTime);
        movePlayer(targetPos, deltaTime);
        mapObjects[nextCubePos.x][nextCubePos.y] = gameObjectFactory.create(GameObjectType::LIGHT_OBJECT, nextCubePos.x, nextCubePos.y); //place cube
    }
}
