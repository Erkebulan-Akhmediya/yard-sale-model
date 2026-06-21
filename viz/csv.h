#ifndef CSV_H
#define CSV_H

#include <stdio.h>

typedef struct {
    char *_name;
    int row_count, col_count, max;
    FILE *_file;
} CSV;

CSV *csv_open(char *);

float *csv_get_line(CSV *, int);

#endif