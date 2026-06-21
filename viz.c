#include "raylib.h"
#include "dstr.h"
#include <stdio.h>
#include <stdlib.h>

#define WIN_wIDTH 700
#define WIN_HEIGHT 500
#define WIN_TITLE "Yard Sale Model"

#define AXIS_WIDTH 3
#define AXIS_PADDING 50

int count_data(float *max, int *row_count, int *col_count) {
    FILE *f = fopen("ysm.csv", "r");
    if (f == NULL)
        return -1;

    int ch;
    DStr *num_dstr = new_dstr();
    int count = 0;
    *row_count = 0;
    *col_count = 0;
    *max = 0.0;
    while ((ch = fgetc(f)) != EOF) {
        if (ch != ',' && ch != '\n') {
            dstr_append(num_dstr, ch);
            continue;
        }

        count++;
        char *num_str = dstr_to_str(num_dstr);
        float num = (float) atof(num_str);
        dstr_clear(num_dstr);

        if (ch == '\n')
            (*row_count)++;
        
        if (num > *max)
            *max = num;
    }

    *col_count = count / *row_count;

    dstr_free(num_dstr);
    fclose(f);
    return 0;
}

void skip_lines(FILE *f, int nlines) {
    if (nlines == 0)
        return;
    
    int new_line_count = 0;
    int ch;
    while ((ch = fgetc(f)) != EOF) {
        if (ch == '\n')
            new_line_count++;
        if (nlines == new_line_count)
            break;
    }
}

float *read_line(int row_index, int row_len) {
    FILE *f = fopen("ysm.csv", "r");
    if (f == NULL)
        return NULL;
    
    skip_lines(f, row_index);
    float *line = calloc(row_len, sizeof(float));
    int next_free_index = 0;
    int ch;
    DStr *num_dstr = new_dstr();
    while ((ch = fgetc(f)) != EOF) {
        if (ch != ',' && ch != '\n') {
            dstr_append(num_dstr, ch);
            continue;
        }
        char *num_str = dstr_to_str(num_dstr);
        float num = (float) atof(num_str);
        line[next_free_index++] = num;
        dstr_clear(num_dstr);

        if (ch == '\n')
            break;
    }
    dstr_free(num_dstr);
    fclose(f);
    return line;
}

int main() {

    float max;
    int row_count, col_count;
    if (count_data(&max, &row_count, &col_count) == -1) {
        perror("failed to count data");
        return -1;
    }
    printf("max: %f\nrow count: %d\ncol count: %d\n", max, row_count, col_count);

    // read and print first 3 rows (for testing)
    for (int row_index = 0; row_index < 3; row_index++) {
        printf("row %d: ", row_index);
        float *line = read_line(row_index, col_count);
        if (line == NULL) {
            perror("failed to read a line");
            continue;
        }
        for (int i = 0; i < col_count; i++)
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