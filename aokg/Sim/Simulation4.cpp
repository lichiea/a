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
    // Устанавливаем признак того, что окно нуждается в перерисовке
    glutPostRedisplay();
}
