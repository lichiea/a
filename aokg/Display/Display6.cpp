#include "Display.h"
using namespace glm;
bool isOrthographic = false;
float Sscale = 0.3;


void zoomOrt(float distance) {
    Sscale += distance * 0.05;
    if (Sscale < 0.3) Sscale = 0.3;
    if (Sscale > 2.3) Sscale = 2.3;
    reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}


void setProjection(int width, int height) {
    if (isOrthographic) {
        float aspect = (float)width / height;
        float orthoHeight = 10.0 * Sscale; // высота на ближней плоскости
        float orthoWidth = 10.0 * Sscale;
        if (aspect >= 1.0) { glOrtho(-aspect * orthoWidth, aspect * orthoWidth, -orthoHeight, orthoHeight, 0.2, 70.0); }
        else { glOrtho(-orthoWidth, orthoWidth, -orthoHeight / aspect, orthoHeight / aspect, 0.2, 70.0); }

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
        cam.rotateUpDown(sTime * 50);
    }
    if (GetAsyncKeyState(VK_DOWN)) {
        cam.rotateUpDown(-50 * sTime);
    }
    if (GetAsyncKeyState(VK_LEFT)) {
        cam.rotateLeftRight(sTime * 50);
    }
    if (GetAsyncKeyState(VK_RIGHT)) {
        cam.rotateLeftRight(-50 * sTime);
    }
    if (GetAsyncKeyState(0xBB)) {
        if (isOrthographic) zoomOrt(-50*sTime);
        else cam.zoomInOut(-50 * sTime);
    }
    if (GetAsyncKeyState(0xBD)) {
        if (isOrthographic) zoomOrt(sTime * 50);
        else cam.zoomInOut(sTime * 50);
    }
    if (GetAsyncKeyState(VK_RBUTTON)) {
        isOrthographic = !isOrthographic; // Переключаем флаг
        if (isOrthographic == true) cout << "or ";
        else cout << "per ";
        int width = glutGet(GLUT_WINDOW_WIDTH);
        int height = glutGet(GLUT_WINDOW_HEIGHT);
        //setProjection(width, height); // Обновляем проекцию
        reshape(width,height); // Перерисовываем сцену
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
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    // устанавливаем камеру
    cam.apply();
    // устанавливаем источник света
    light.apply(GL_LIGHT0);
    // выводим все графические объекты
    //for (auto& go : graphicObjects) {
    //    go->draw();
    //}
    m.draw();
    // Отключаем вершинные массивы
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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
    std::string title = "Laba_6. FPS [" + std::to_string(fps) + "]";
    glutSetWindowTitle(title.c_str());
}
