#include <stdio.h>
#include <stdlib.h>
#include "dstr.h"
#include "csv.h"

CSV *csv_open(char *file_name) {
    CSV *csv = malloc(sizeof(CSV));
    if (csv == NULL)
        return NULL;

    csv->_name = file_name;
    csv->row_count = 0;
    csv->col_count = 0;
    csv->max = 0.0;
    csv->_file = fopen(file_name, "r");
    if (csv->_file == NULL) {
        free(csv);
        return NULL;
    }

    DStr *num_dstr = new_dstr();
    if (num_dstr == NULL)
        return NULL;
    int count = 0, ch;
    while ((ch = fgetc(csv->_file)) != EOF) {
        if (ch != ',' && ch != '\n') {
            dstr_append(num_dstr, ch);
            continue;
        }

        count++;
        char *num_str = dstr_to_str(num_dstr);
        float num = (float) atof(num_str);
        dstr_clear(num_dstr);

        if (ch == '\n')
            csv->row_count++;
        
        if (num > csv->max)
            csv->max = num;
    }

    csv->col_count = count / csv->row_count;

    dstr_free(num_dstr);
    fclose(csv->_file);
    return csv;
}

void _csv_skip_lines(CSV *csv, int nlines) {
    if (nlines == 0)
        return;
    
    int new_line_count = 0;
    int ch;
    while ((ch = fgetc(csv->_file)) != EOF) {
        if (ch == '\n')
            new_line_count++;
        if (nlines == new_line_count)
            break;
    }
}

float *csv_get_line(CSV *csv, int row_index) {
    csv->_file = fopen(csv->_name, "r");
    if (csv->_file == NULL)
        return NULL;
    
    _csv_skip_lines(csv, row_index);
    float *line = calloc(csv->col_count, sizeof(float));
    int next_free_index = 0;
    int ch;
    DStr *num_dstr = new_dstr();
    while ((ch = fgetc(csv->_file)) != EOF) {
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
    fclose(csv->_file);
    return line;
}
