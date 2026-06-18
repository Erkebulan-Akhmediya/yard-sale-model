#include "raylib.h"
#include <stdio.h>

#define WIN_wIDTH 700
#define WIN_HEIGHT 500
#define WIN_TITLE "Yard Sale Model"

#define AXIS_WIDTH 3
#define AXIS_PADDING 50

int main() {

    InitWindow(WIN_wIDTH, WIN_HEIGHT, WIN_TITLE);

    if (!IsWindowReady()) {
        perror("Failed to init window");
        return 1;
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        // draw x-axis
        DrawRectangle(AXIS_PADDING, WIN_HEIGHT - AXIS_PADDING, WIN_wIDTH - (2 * AXIS_PADDING), AXIS_WIDTH, GRAY);

        // draw y-axis
        DrawRectangle(AXIS_PADDING, AXIS_PADDING, AXIS_WIDTH, WIN_HEIGHT - (2 * AXIS_PADDING), GRAY);

        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}