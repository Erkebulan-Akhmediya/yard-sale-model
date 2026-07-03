#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include "bst.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    float removed[2];
    float added[2];
} ExchangeResult;

bool csv = false;

void random_pair(int *i, int *j, int max) {
    *i = rand() % max;
    *j = rand() % max;
    if (*i == *j)
        random_pair(i, j, max);
}

bool coin_flip() {
    return rand() % 2 == 1;
}

int exchange(float *arr, BST *bst) {
    int i, j;
    random_pair(&i, &j, bst->size);
    float amount = MIN(arr[i], arr[j]) * 0.1;
    ExchangeResult res;
    res.removed[0] = arr[i];
    res.removed[1] = arr[j];
    if (coin_flip()) {
        arr[i] += amount;
        arr[j] -= amount;
    } else {
        arr[j] += amount;
        arr[i] -= amount;
    }
    res.added[0] = arr[i];
    res.added[1] = arr[j];
    
    if (!csv)
        return 0;

    if (bst_delete(bst, res.removed[0]) == -1) {
        fprintf(stderr, "failed to delete %.2f from the BST\n", res.removed[0]);
        fprintf(
            stderr, 
            "exchange result: removed: [%.2f, %.2f], added: [%.2f, %.2f]\n", 
            res.removed[0], 
            res.removed[1], 
            res.added[0], 
            res.added[1]
        );
        return -1;
    }
    if (bst_delete(bst, res.removed[1]) == -1) {
        fprintf(stderr, "failed to delete %.2f from the BST\n", res.removed[0]);
        fprintf(
            stderr, 
            "exchange result: removed: [%.2f, %.2f], added: [%.2f, %.2f]\n", 
            res.removed[0], 
            res.removed[1], 
            res.added[0], 
            res.added[1]
        );
        return -1;
    }
    if (bst_insert(bst, res.added[0]) == -1) {
        fprintf(stderr, "failed to delete %.2f from the BST\n", res.removed[0]);
        fprintf(
            stderr, 
            "exchange result: removed: [%.2f, %.2f], added: [%.2f, %.2f]\n", 
            res.removed[0], 
            res.removed[1], 
            res.added[0], 
            res.added[1]
        );
        return -1;
    }
    if (bst_insert(bst, res.added[1]) == -1) {
        fprintf(stderr, "failed to delete %.2f from the BST\n", res.removed[0]);
        fprintf(
            stderr, 
            "exchange result: removed: [%.2f, %.2f], added: [%.2f, %.2f]\n", 
            res.removed[0], 
            res.removed[1], 
            res.added[0], 
            res.added[1]
        );
        return -1;
    }

    return 0;
}

void write_to_csv(FILE *file, float *arr, int arr_size) {
    for (int i = 0; i < arr_size; i++) {
        fprintf(file, "%.2f", arr[i]);
        if (i < arr_size - 1)
            fprintf(file, ",");
    }
    fprintf(file, "\n");
}

int compare(const void *a, const void *b) {
    float float_a = *(const float *)a;
    float float_b = *(const float *)b;
    
    if (float_a < float_b) return 1;
    if (float_a > float_b) return -1;
    return 0;
}

int main(int argc, char *argv[]) {

    csv = false;
    FILE *file;
    if (argc == 3 && strcmp(argv[1], "--export") == 0) {
        csv = true;
        file = fopen(argv[2], "w");
        if (file == NULL) {
            perror("Error opening/creating file");
            return 1;
        }
    }

    srand(time(NULL));
    
    int exchange_num;
    printf("number of exchanges: ");
    scanf("%d", &exchange_num);
    
    int people_num;
    printf("number of people: ");
    scanf("%d", &people_num);

    int initial_cap;
    printf("initial capital: ");
    scanf("%d", &initial_cap);

    float *arr = calloc(people_num, sizeof(float));
    if (arr == NULL) {
        perror("failed to allocate arr\n");
        return 1;
    }
    for (int i = 0; i < people_num; i++)
        arr[i] = initial_cap;
    
    BST bst;
    if (bst_init_with_arr(&bst, arr, people_num) == -1) {
        fprintf(stderr, "failed to init the BST\n");
        return 1;
    }
    if (bst.size != people_num) {
        fprintf(stderr, "the BST did not initialize properly\n");
        return 1;
    }

    if (csv)
        write_to_csv(file, arr, people_num);

    for (int i = 0; i < exchange_num; i++) {
        if (exchange(arr, &bst) == -1) {
            fprintf(stderr, "exchange failed\n");
            return 1;
        }
        if (csv) {
            float *sorted_arr = bst_to_arr(&bst);
            if (sorted_arr == NULL) {
                fprintf(stderr, "failed to turn the BST into an array\n");
                return 1;
            }
            write_to_csv(file, sorted_arr, people_num);
            free(sorted_arr);
        }
    }

    qsort(arr, people_num, sizeof(int), compare);

    for (int i = 0; i < people_num; i++)
        printf("%.2f\n", arr[i]);

    free(arr);

    if (csv && fclose(file) != 0) 
        fprintf(stderr, "failed to close the file: %d\n", errno);

    return 0;
}