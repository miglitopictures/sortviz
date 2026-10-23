#include <stdarg.h>
#include <stdio.h>
#include <time.h>

/* Timer */

// Iniciar o 'timer' (capturando o momento atual e salvando-o em uma variavel passada por referencia)
void start_timer(clock_t *start) {
    *start = clock();
}

// Para o 'timer' (capturando o momento final e exibindo-o na tela)
double end_timer(char *prop_string, clock_t start) {
    double time_elapsed = (double) (clock() - start);
    printf("%-24s | %.0f\n", prop_string, time_elapsed);
    return time_elapsed;
}


void print_array(int *arr, int size) {
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");
}

void sort_bubble_early_stop(int *arr, int size)
{    
    int array_in_order = 0; // iniciamos presumindo que o array esta desordenado
    int end = size-1;
    while (!array_in_order) {
        array_in_order = 1;

        for (int i = 0; i < end; i++) {
            // se temos um valor menor apos um valor maior
            if (arr[i] > arr[i+1]) {
                // nao estamos em ordem ainda
                array_in_order = 0;
                
                // swap values
                int tmp = arr[i+1];
                arr[i+1] = arr[i];
                arr[i] = tmp;
            }
        }

        end -= 1; // diminuimos o end, pois o valor mais alto ocupa o final do array a cada iteracao.
    }
}


// metodo classico, rodamos o array inteiro sem
void sort_bubble_classic(int arr[], int size)
{
    for (int j = 0; j < size - 1; j++)
    {
        for (int i = 0; i < size - 1; i++)
        {
            if (arr[i] > arr[i+1]) {
                //swap
                int tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
            }
        }
    }
}

int main(int argc, char *argv[]) {

    clock_t timer;

    int ITERATIONS = 32;
    if (argc > 1)
    {
        sscanf(argv[1], "%d", &ITERATIONS);
    }

    const int SIZE = ITERATIONS * ITERATIONS;
    int setA[SIZE];
    int setB[SIZE];


    for (int j = 0; j < ITERATIONS; j++)
    {
        for (int i = 0; i < ITERATIONS; i++)
        {
            setA[i + (j * ITERATIONS)] = i;
            setB[i + (j * ITERATIONS)] = i;
        }
        
    }


    printf("---- sorting an array with %d elements ----\n\n", SIZE);

    // print header
    printf("%-24s | time\n", "operation");
    for (int i = 0; i < (24 + 10); i++) printf("-");
    printf("\n");
    
    // classic bubble sort (double nested, no early stop)
    start_timer(&timer);
    sort_bubble_classic(setA, SIZE);
    double time_classic = end_timer("bubble (classic)", timer);
    
    // improvement with early stop when sorted
    start_timer(&timer);
    sort_bubble_early_stop(setB, SIZE);
    double time_early_stop = end_timer("bubble (early stop)", timer);

    printf("\nclassic is %.2f times slower then the alternative...\n", time_classic/time_early_stop);


    return 0;
}