#include "raylib.h"
#include "dstr.h"
#include "csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIN_WIDTH 1200
#define WIN_HEIGHT 900
#define WIN_TITLE "Yard Sale Model"

#define AXIS_WIDTH 3
#define AXIS_PADDING 50

#define COL_PAD 3
#define COL_COLOR BLUE

void draw_col(int x, int y, int width, int height) {
    x += COL_PAD;
    width -= COL_PAD;
    DrawRectangle(x, y, width, height, COL_COLOR);
}

int main(int argc, char *argv[]) {

    if (argc != 3 || strcmp(argv[1], "-f") != 0) {
        perror("invalid arguments");
        return 1;
    }

    CSV *csv = csv_open(argv[2]);
    if (csv == NULL) {
        perror("failed to open csv");
        return 1;
    }

    InitWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);

    if (!IsWindowReady()) {
        perror("Failed to init window");
        return 1;
    }

    int row_index = 0;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        int x_width = WIN_WIDTH - (2 * AXIS_PADDING);
        int y_height = WIN_HEIGHT - (2 * AXIS_PADDING);
        int col_width = x_width / csv->col_count;

        // draw x-axis
        DrawRectangle(AXIS_PADDING, WIN_HEIGHT - AXIS_PADDING, x_width, AXIS_WIDTH, GRAY);

        // draw y-axis
        DrawRectangle(AXIS_PADDING, AXIS_PADDING, AXIS_WIDTH, y_height, GRAY);

        int init_col_x = AXIS_PADDING + AXIS_WIDTH;
        int init_col_y = WIN_HEIGHT - AXIS_PADDING - AXIS_WIDTH;

        if (GetMouseWheelMove() < 0)
            if (row_index < csv->row_count-1)
                row_index++;
            else
                row_index = 0;
        else if (GetMouseWheelMove() > 0) 
            if (row_index > 0)
                row_index--;
            else
                row_index = csv->row_count-1;
        
        char iteration[64];
        sprintf(iteration, "%d/%d", row_index, csv->row_count-1);
        DrawText(iteration, WIN_WIDTH-100, 100, 14, BLACK);

        float *line = csv_get_line(csv, row_index);
        if (line == NULL) {
            EndDrawing();
            break;
        }
        for (int i = 0; i < csv->col_count; i++) {
            int col_height = y_height * (line[i] / csv->max);
            int col_x = init_col_x + i * col_width;
            int col_y = init_col_y - col_height;
            draw_col(col_x, col_y, col_width, col_height);
        }
        free(line);

        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}