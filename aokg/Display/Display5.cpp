#include "Display.h"
using namespace glm;
bool isOrthographic = true;

void setProjection(int width, int height) {
    if (isOrthographic) {
        float aspect = (float)width / height;
        float orthoHeight = 0.2 * tan(25.0 * 0.5 * 3.14 / 180.0); // высота на ближней плоскости
        float orthoWidth = orthoHeight * aspect;
        glOrtho(-10.05875, 10.05875, -10.04406, 10.04406, -70.0, 70.0);
    }
    else {
        gluPerspective(25.0, (float)width / height, 0.2, 70.0);
    }

}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //setProjection(width, height);
    gluPerspective(25.0, (float)width / height, 0.2, 70.0);
    glMatrixMode(GL_MODELVIEW);
}

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
    if (GetAsyncKeyState(VK_RBUTTON)) {
        isOrthographic = !isOrthographic; // Переключаем флаг
        if (isOrthographic == true) cout << "or";
        else cout << "per";
        int width = glutGet(GLUT_WINDOW_WIDTH);
        int height = glutGet(GLUT_WINDOW_HEIGHT);
        setProjection(width, height); // Обновляем проекцию
        glutPostRedisplay(); // Перерисовываем сцену
    }
}


void display(void) {

    // отчищаем буфер цвета и буфер глубины
    if (isOrthographic == true) glClearColor(0.00, 0.00, 0.00, 1.0);
    else glClearColor(1.00, 1.00, 1.00, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // включаем тест глубины
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    // устанавливаем камеру
    cam.apply();
    // устанавливаем источник света
    light.apply(GL_LIGHT0);
    // выводим все графические объекты
    for (auto& go : graphicObjects) {
        go.draw();
    }
    // смена переднего и заднего буферов
    glutSwapBuffers();
    processInput(simulationTime);

    getFPS();

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
    std::string title = "Laba_5. FPS [" + std::to_string(fps) + "]";
    glutSetWindowTitle(title.c_str());
}

