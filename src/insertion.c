#include <stdio.h>

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


void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void print_array(int *arr, int len) {
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}


void insertion_sort(int *arr, int n) {

    for (int i = 1; i < n; i++) {

        int current = arr[i];
        int j = i-1;

        while (j >= 0 && arr[j] > current) {
            arr[j+1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = current;
    }
}


// 9, 5, 16, 1, 6
void shell_sort(int *arr, int n) {

    //
    for (int gap = n/2; gap >= 1; gap = gap / 2) {
        
        for (int i = gap; i < n; i++) {
            int current = arr[i];
            int j = i - gap;

            while (j >= 0 && arr[j] > current) {
                arr[j + gap] = arr[j];
                j = j - gap;
            }

            arr[j+gap] = current;

        }
    }
}

void quick_sort(int *arr, int low, int high) {
    // caso base, low >= high significa que terminamos de verificar o subarray
    if (low < high) {
        // step 1: escolhemos o pivo; (ignorando esse problema por enquanto, pegamos o ultimo item)
        int pivot = arr[high];
    
        // step 2: particionamos usando o metodo de Hoare;
        int i = low - 1, j = high;
    
        while(1) {
            // procuramos um valor maior
            // que o pivo na esqueda 
            do {
                i++;
            } while (arr[i] < pivot);

            // e um valor MENOR
            // que o pivo na direita 
            do {
                j--;
            } while (arr[j] > pivot);

            if (i >= j) break; // se ja verificamos todos os valores, podemos sair do loop e fazer o ultimo swap
    
            swap(&arr[i],&arr[j]); // trocamos  e passamos pra proxima iteracao
            
        }
        
        // passo 3: pivô na posição final (i é o index novo do pivo)
        swap(&arr[i], &arr[high]);
        
        quick_sort(arr, low, i-1);
        quick_sort(arr, i+1, high);
    }

}


int main()
{

    int SIZE = 6;
    int a[] = { 1, 72, 3, 8, 22, 93 };
    print_array(a, SIZE);
    quick_sort(a, 0, SIZE-1);
    print_array(a, SIZE);

    return 0;
}
