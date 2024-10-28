#include "Display.h"

void processInput(float sTime) {
    if (GetAsyncKeyState(VK_UP)) {
        cam.rotateUpDown(sTime*50);
    }
    if (GetAsyncKeyState(VK_DOWN)) {
        cam.rotateUpDown(-50* sTime);
    }
    if (GetAsyncKeyState(VK_LEFT)) {
        cam.rotateLeftRight(sTime*50);
    }
    if (GetAsyncKeyState(VK_RIGHT)) {
        cam.rotateLeftRight(-50* sTime);
    }
    if (GetAsyncKeyState(0xBB)) {     
        cam.zoomInOut(-50* sTime);
    }
    if (GetAsyncKeyState(0xBD)) {  
        cam.zoomInOut(sTime*50);
    }
}

void display(void) {
    getFPS();
    processInput(simulationTime);
    // отчищаем буфер цвета и буфер глубины
    glClearColor(0.00, 0.00, 0.00, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // включаем тест глубины
    glEnable(GL_DEPTH_TEST);
    // устанавливаем камеру
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    cam.apply();
    // выводим все графические объекты
    for (auto& go : graphicObjects) {
        go.draw();
    }
    // смена переднего и заднего буферов
    glutSwapBuffers();
};

void getFPS() {
    LARGE_INTEGER currentCounter;
    QueryPerformanceCounter(&currentCounter); // Получаем текущий отсчет
    // Увеличиваем счетчик кадров
    frameCount++;
    // Вычисляем время с последнего обновления FPS
    float elapsedTime = static_cast<float>(currentCounter.QuadPart - lastFPSCounter.QuadPart) / frequency.QuadPart;
    if (elapsedTime >= 1.0) { // Обновляем каждую секунду
        fps = static_cast<float>(frameCount) / elapsedTime; // Вычисляем FPS
        frameCount = 0; // Сбрасываем счетчик кадров
        lastFPSCounter = currentCounter; // Обновляем последний отсчет для FPS
    }
    std::string title = "Laba_4. FPS [" + std::to_string(fps) + "]";
    glutSetWindowTitle(title.c_str());
}
