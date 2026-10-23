#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

void start_timer(clock_t *start) {
    *start = clock();
}

double end_timer(clock_t start) {
    double time_elapsed = (double) (clock() - start);
    return time_elapsed;
}

typedef struct Stats {
    int comparasion_count;
    int swap_count;
    double time_elapsed;
} Stats;

void swap(int a, int b, int *arr) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

Stats bubble_sort_v1(int *arr, int size) {
    
    Stats stats = {0}; // for benchmarking only

    clock_t timer;
    start_timer(&timer);

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                swap(j,j+1, arr);
                stats.swap_count += 1;
            }
            stats.comparasion_count += 1;
        }
    }

    stats.time_elapsed = end_timer(timer);

    return stats;

}

Stats bubble_sort_v2(int *arr, int size) {

    Stats stats = {0}; // for benchmarking only

    clock_t timer;
    start_timer(&timer);

    for (int i = 1; i < size; i++)
    {
        for (int j = 0; j < size - i; j++)
        {
            if (arr[j] > arr[j+1])
            {
                swap(j,j+1, arr);
                stats.swap_count += 1;
            }
            stats.comparasion_count += 1;
        }
    }

    stats.time_elapsed = end_timer(timer);

    return stats;

}

Stats bubble_sort_v3(int *arr, int size) {
    
    Stats stats = {0}; // for benchmarking only

    clock_t timer;
    start_timer(&timer);

    bool sorted = false;
    int i = 1;
    while (!sorted)
    {
        sorted = true;

        for (int j = 0; j < size - i; j++)
        {
            if (arr[j] > arr[j+1])
            {
                swap(j,j+1, arr);
                sorted = false;
                stats.swap_count += 1;
            }
            stats.comparasion_count += 1;
        }

        i++;
    }

    stats.time_elapsed = end_timer(timer);

    return stats;

}

Stats selection_sort(int *arr, int size) {
    
    Stats stats = {0}; // for benchmarking only

    clock_t timer;
    start_timer(&timer);

    for (int i = 0; i < size - 1; i++)
    {
        int smallest = i;
        for (int j = i+1; j < size; j++)
        {
            if (arr[smallest] > arr[j])
            {
                smallest = j;
            }
            stats.comparasion_count += 1;
        }
        
        if (smallest != i) {
            swap(i, smallest, arr);
            stats.swap_count += 1;
        }
    }

    stats.time_elapsed = end_timer(timer);

    return stats;

}

void print_array(char *message, int *arr, int size) {
    printf("%s > ", message);
    for (int i = 0; i < size; i++) {
        printf("%d - ", arr[i]);
    }
    printf("\n");
}


void print_algo_stats(char *name, Stats stats) {
    printf("%-26s | comparassions: %-7d |swaps: %-7d | ticks: %-7.0f\n", name, stats.comparasion_count, stats.swap_count, stats.time_elapsed);
}

int main() {
    srand(1); // fixed seed for now


    int SIZE = 1200;
    int arrA[SIZE], arrB[SIZE], arrC[SIZE], arrD[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        int random_value = rand() % (SIZE*2);
        arrA[i] = random_value;
        arrB[i] = random_value;
        arrC[i] = random_value;
        arrD[i] = random_value;
    }

    // print_array("a", arrA, SIZE);
    // print_array("b", arrB, SIZE);
    // print_array("c", arrC, SIZE);
    // print_array("d", arrD, SIZE);
    
    Stats stats_a, stats_b, stats_c, stats_d;

    stats_a = bubble_sort_v1(arrA, SIZE);
    stats_b = bubble_sort_v2(arrB, SIZE);
    stats_c = bubble_sort_v3(arrC, SIZE);
    stats_d = selection_sort(arrD, SIZE);

    printf("============---=========== sorting a %d element array ==========================\n", SIZE);
    print_algo_stats("bubble sort (naive)", stats_a);
    print_algo_stats("bubble sort (check up-to)", stats_b);
    print_algo_stats("bubble sort (early stop)", stats_c);
    print_algo_stats("selection sort", stats_d);

    // print_array("a", arrA, SIZE);
    // print_array("b", arrB, SIZE);
    // print_array("c", arrC, SIZE);
    // print_array("d", arrD, SIZE);
}
