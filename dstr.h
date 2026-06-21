#ifndef DSTR_H
#define DSTR_H

typedef struct {
    char *buff;
    int next_free_index;
} DStr;

DStr *new_dstr();
void dstr_append(DStr *, char);
char *dstr_to_str(DStr *);
void dstr_clear(DStr *);
void dstr_free(DStr *);

#endif