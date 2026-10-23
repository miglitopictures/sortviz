// a simple testing program for thinking about sorting

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
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

    return stats;

}

Stats bubble_sort_v2(int *arr, int size) {

    Stats stats = {0}; // for benchmarking only

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

    return stats;

}

Stats bubble_sort_v3(int *arr, int size) {
    
    Stats stats = {0}; // for benchmarking only

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

    return stats;

}

Stats selection_sort(int *arr, int size) {
    
    Stats stats = {0}; // for benchmarking only

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


void bench_sort(Stats (*func)(int *arr, int size), int *base_array, int count, char *message) {
    Stats stats = {0}; // for benchmarking only
    clock_t timer;
    
    int array[count];
    for (int i = 0; i < count; i++)
    {
        array[i] = base_array[i];
    }
    
    start_timer(&timer);
    stats = func(array, count);
    stats.time_elapsed = end_timer(timer);

    print_algo_stats(message, stats);
}

int main(int argc, char *argv[]) {
    srand(1); // fixed seed for now


    int SIZE = 1200;
    if (argc > 1) {
        sscanf(argv[1], "%d", &SIZE);
    }
    printf("========================== sorting a %d element array ==========================\n", SIZE);

    int array[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        int random_value = rand() % (SIZE*2);
        array[i] = random_value;
    }

    bench_sort(bubble_sort_v1, array, SIZE, "bubble sort (naive)");
    bench_sort(bubble_sort_v2, array, SIZE, "bubble sort (check up-to)");
    bench_sort(bubble_sort_v3, array, SIZE, "bubble sort (early stop)");
    bench_sort(selection_sort, array, SIZE, "selection sort");
}
