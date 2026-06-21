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

    bool csv = false;
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
        perror("failed to allocate arr");
        return 1;
    }
    for (int i = 0; i < people_num; i++)
        arr[i] = initial_cap;
    
    float *sorted_arr = calloc(people_num, sizeof(float));
    if (sorted_arr == NULL) {
        perror("failed to allocate sorted_arr");
        return 1;
    }

    if (csv)
        write_to_csv(file, arr, people_num);

    for (int i = 0; i < exchange_num; i++) {
        exchange(arr, people_num);
        if (csv) {
            memcpy(sorted_arr, arr, sizeof(float) * people_num);
            qsort(sorted_arr, people_num, sizeof(float), compare);
            write_to_csv(file, sorted_arr, people_num);
        }
    }

    qsort(arr, people_num, sizeof(int), compare);

    for (int i = 0; i < people_num; i++)
        printf("%.2f\n", arr[i]);

    free(arr);
    free(sorted_arr);

    if (csv && fclose(file) != 0) 
        printf("failed to close the file: %d\n", errno);

    return 0;
}