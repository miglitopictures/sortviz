// a simple testing program
// for thinking about,
// and testing, 
// sorting algorithms

// by miguel duarte de barros (miglito)

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

// starts the "timer"
void start_timer(clock_t *start) {
    *start = clock();
}

// ends the "timer", returning the elapsed time
double end_timer(clock_t start) {
    double time_elapsed = (double) (clock() - start);
    return time_elapsed;
}

// bencharking data we are tracking
typedef struct Stats {
    long long int comparasion_count;
    int swap_count;
    double time_elapsed;
} Stats;

// swaps two values in a array.
void swap(int idx_a, int idx_b, int *arr) {
    int temp = arr[idx_a];
    arr[idx_a] = arr[idx_b];
    arr[idx_b] = temp;
}


// checks if an array is sorted, returns false as soon as it fails
bool is_sorted(int *arr, int n) {
    for (int i = 0; i < n-1; i++)
    {
        if (arr[i] > arr[i+1])
        {
            return false;
        }
    }

    return true;
}

// sorting algos //

// classic academic version of a simple bubble sort.
Stats bubble_sort_v1(int *arr, int size) {

    Stats stats = {0};
    
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

// simple optimization so we check only up to where the array is unsorted. (j < size - i)
Stats bubble_sort_v2(int *arr, int size) {
    
    Stats stats = {0};

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

// improving it further with a early stop when array is already fully sorted.
Stats bubble_sort_v3(int *arr, int size) {
    
    Stats stats = {0};

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

// basic selection sort algo
Stats selection_sort(int *arr, int size) {
    
    Stats stats = {0};

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

// Stats insertion_sort_v2(int *arr, int size) {
    
//     Stats stats = {0};

//     for (int i = 1; i < size; i++)
//     {
//         for (int j = i; j > 0; j--) {
//             stats.comparasion_count += 1;
//             if (arr[j-1] > arr[j])
//             {
//                 swap(j-1, j, arr);
//                 stats.swap_count += 1;
//             }
//             else
//             {
//                 break;
//             }
            
//         }
//     }

//     return stats;
// }

Stats insertion_sort_v1(int *arr, int size) {
    
    Stats stats = {0};

    for (int i = 1; i < size; i++)
    {
        for (int j = i; j > 0; j--) {
            stats.comparasion_count += 1;
            if (arr[j-1] > arr[j])
            {
                swap(j-1, j, arr);
                stats.swap_count += 1;
            }
            else
            {
                break;
            }
            
        }
    }

    return stats;
}

Stats insertion_sort_v2(int *arr, int size) {
    Stats stats = {0};

    for (int i = 1; i < size; i++) {
        int current = arr[i];

        int j = i-1;

        while (j >= 0 && arr[j] > current) {
            arr[j+1] = arr[j];
            stats.comparasion_count++;
            stats.swap_count++;
            j--;
        }

        arr[j+1] = current;
    }

    return stats;
}

Stats shell_sort_v1(int *arr, int n) {

    Stats stats = {0};

    for (int gap = n/2; gap > 0; gap = gap / 2) {
        
        for (int i = gap; i < n; i++) {
            int current = arr[i];
            int j = i - gap;

            while (j >= 0 && arr[j] > current) {
                stats.comparasion_count++;
                stats.swap_count++;
                arr[j + gap] = arr[j];
                j = j - gap;
            }

            arr[j+gap] = current;

        }
    }


    return stats;
}

// prints an array 'arr' with a starting 'message', given its 'size'. 
void print_array(char *message, int *arr, int size) {
    printf("%s > ", message);
    for (int i = 0; i < size; i++) {
        printf("%d - ", arr[i]);
    }
    printf("\n");
}

// print a line for the benchmarking table
void print_algo_stats(char *name, Stats stats) {
    printf("%-26s | ", name);
    printf("%s: %-9lld | ", "comparassions", stats.comparasion_count);
    printf("%s: %-9d | ", "swaps", stats.swap_count);
    printf("%s: %-9.0f" , "ticks", stats.time_elapsed);
    printf("\n");
}


//  tests a simple sorting function given its function pointer 'func',
// 'base_array' will be copied for testing
// 'count' is the size of base_array
// 'message' is the string that will appear in the formatted printing
// example of the output:
// > bubble sort (naive)        | comparassions: 361      |swaps: 108      | ticks: 9 
void bench_sort(Stats (*func)(int *arr, int size), int *base_array, int count, char *message) {
    Stats stats = {0};
    clock_t timer;
    
    // create a new array with the same size of the original and copy its data
    int array[count];
    for (int i = 0; i < count; i++) { array[i] = base_array[i]; }
    
    // call the sorting function and time its execution.
    start_timer(&timer);
    stats = func(array, count);
    stats.time_elapsed = end_timer(timer);

    // print the stats for the algorithm
    if (is_sorted(array, count))
    {
        print_algo_stats(message, stats);
    }
    else
    {
        printf("%s has not worked xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n", message);
    }
    
}


int main(int argc, char *argv[]) {
    srand(0); // time(0)

    // set default test array size to 1200, unless given as an argument
    int SIZE = 1200;
    if (argc > 1) {
        sscanf(argv[1], "%d", &SIZE);
    }

    // create and fill the test array with random integers.
    int array[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        int random_value = rand() % (SIZE*2);
        array[i] = random_value;
    }

    // program header
    printf("=========================== sorting a %d element array ===========================\n", SIZE);

    // test and print stats for each sorting algo
    bench_sort(bubble_sort_v1, array, SIZE, "bubble sort (naive)");
    bench_sort(bubble_sort_v2, array, SIZE, "bubble sort (check up-to)");
    bench_sort(bubble_sort_v3, array, SIZE, "bubble sort (early stop)");
    bench_sort(selection_sort, array, SIZE, "selection sort");
    bench_sort(insertion_sort_v1, array, SIZE, "insertion sort (v1)");
    bench_sort(insertion_sort_v2, array, SIZE, "insertion sort (v2)");
    bench_sort(shell_sort_v1, array, SIZE, "shell sort (v1)");
}
