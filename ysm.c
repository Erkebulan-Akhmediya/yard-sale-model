#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void random_pair(int *i, int *j, int max) {
    *i = rand() % (max+1);
    *j = rand() % (max+1);
}

unsigned short coin_flip() {
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

int compare(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    
    if (int_a < int_b) return 1;
    if (int_a > int_b) return -1;
    return 0;
}

int main() {

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

    for (int i = 0; i < exchange_num; i++)
        exchange(arr, people_num);

    qsort(arr, people_num, sizeof(int), compare);

    for (int i = 0; i < people_num; i++)
        printf("%.2f\n", arr[i]);

    free(arr);

    return 0;
}