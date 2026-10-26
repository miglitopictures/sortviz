#include <stdio.h>


void print_array(int *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}


void print_array_b(int *arr, int len, int boldId)
{
    for (int i = 0; i < len; i++)
    {
        if (i == boldId) {printf("(%d) ", arr[i]);}
        else {printf("%d ", arr[i]);}
    }

    printf("\n");
}


void insertion_sort(int *arr, int n) {

    for (int i = 1; i < n; i++) {

        int current = arr[i];
        int j = i-1;

        while (j >= 0 && arr[j] > arr[j+1]) {
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




int main()
{

    int SIZE = 6;
    int a[] = { 1, 72, 3, 8, 22, 93 };
    print_array(a, SIZE);
    shell_sort(a, SIZE);
    print_array(a, SIZE);

    return 0;
}
