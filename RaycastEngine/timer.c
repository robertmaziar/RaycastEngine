#include "timer.h"
#include <windows.h>

LARGE_INTEGER frequency;
LARGE_INTEGER tp1, tp2;
double deltaTime;

void start_timer() {
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&tp1);
}

void update_timer() {
    QueryPerformanceCounter(&tp2);
    deltaTime = (double)(tp2.QuadPart - tp1.QuadPart) / frequency.QuadPart;
    tp1 = tp2;
}
