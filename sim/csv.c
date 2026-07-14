#include <stdio.h>
#include <stdbool.h>

bool csv = false;

void write_to_csv(FILE *file, float *arr, int arr_size) {
    for (int i = 0; i < arr_size; i++) {
        fprintf(file, "%.2f", arr[i]);
        if (i < arr_size - 1)
            fprintf(file, ",");
    }
    fprintf(file, "\n");
}