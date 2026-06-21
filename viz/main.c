#include "raylib.h"
#include "dstr.h"
#include "csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIN_wIDTH 700
#define WIN_HEIGHT 500
#define WIN_TITLE "Yard Sale Model"

#define AXIS_WIDTH 3
#define AXIS_PADDING 50

int main(int argc, char *argv[]) {

    if (argc != 3 || argv[1] != "-f")
        perror("invalid arguments");

    CSV *csv = csv_open(argv[2]);
    if (csv == NULL) {
        perror("failed to open csv");
        return 1;
    }

    printf("max: %f\nrow count: %d\ncol count: %d\n", csv->max, csv->row_count, csv->col_count);

    // read and print first 3 rows (for testing)
    for (int row_index = 0; row_index < 3; row_index++) {
        printf("row %d: ", row_index);
        float *line = csv_get_line(csv, row_index);
        if (line == NULL) {
            perror("failed to read a line");
            continue;
        }
        for (int i = 0; i < csv->col_count; i++)
            printf("%.2f ", line[i]);
        printf("\n");
        free(line);
    }

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