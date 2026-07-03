#ifndef CSV_H
#define CSV_H

#include <stdbool.h>

extern bool csv;

void write_to_csv(FILE *file, float *arr, int arr_size);

#endif