#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void random_pair(int *i, int *j, int max) {
    *i = rand() % max;
    *j = rand() % max;
}

bool coin_flip() {
    return rand() % 2 == 1;
}

void exchange(float *arr, int arr_size) {
    int i, j;
    random_pair(&i, &j, arr_size);
    float amount = MIN(arr[i], arr[j]) * 0.1;
    if (coin_flip()) {
        arr[i] += amount;
        arr[j] -= amount;
    } else {
        arr[j] += amount;
        arr[i] -= amount;
    }
}

void write_to_csv(FILE *file, float *arr, int arr_size) {
    for (int i = 0; i < arr_size; i++)
        fprintf(file, "%.2f, ", arr[i]);
    fprintf(file, "\n");
}

int compare(const void *a, const void *b) {
    float int_a = *(const float *)a;
    float int_b = *(const float *)b;
    
    if (int_a < int_b) return 1;
    if (int_a > int_b) return -1;
    return 0;
}

int main(int argc, char *argv[]) {

    bool csv = false;
    FILE *file;
    if (argc > 1 && strcmp(argv[1], "--csv") == 0) {
        csv = true;
        file = fopen("ysm.csv", "w");
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
    for (int i = 0; i < people_num; i++)
        arr[i] = initial_cap;

    for (int i = 0; i < exchange_num; i++) {
        exchange(arr, people_num);
        if (csv) {
            qsort(arr, people_num, sizeof(float), compare);
            write_to_csv(file, arr, people_num);
        }
    }

    qsort(arr, people_num, sizeof(int), compare);

    for (int i = 0; i < people_num; i++)
        printf("%.2f\n", arr[i]);

    free(arr);

    if (csv && fclose(file) != 0) 
        printf("failed to close the file: %d\n", errno);

    return 0;
}