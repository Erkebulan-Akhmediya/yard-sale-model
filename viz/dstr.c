#include <stdlib.h>
#include "dstr.h"

DStr *new_dstr() {
    DStr *str = malloc(sizeof(DStr));
    str->buff = calloc(64, sizeof(char));
    str->next_free_index = 0;
    return str;
}

void dstr_append(DStr *str, char ch) {
    str->buff[str->next_free_index] = ch;
    str->next_free_index++;
}

char *dstr_to_str(DStr *str) {
    str->buff[str->next_free_index] = '\0';
    return str->buff;
}

void dstr_clear(DStr *str) {
    str->next_free_index = 0;
}

void dstr_free(DStr *str) {
    free(str->buff);
    free(str);
}