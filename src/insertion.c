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


void insertion_sort(int *arr, int len) {

    for (int i = 1; i < len; i++) {
        int current = arr[i];
        print_array_b(arr,len,i);

        int j = i-1;

        while (j >= 0) {
            if (arr[j] > arr[j+1]) {
                arr[j+1] = arr[j];
            } else {
                break;
            }
            j--;
        }

        arr[j+1] = current;
    }
}




int main()
{

    int SIZE = 6;
    int a[] = { 1, 72, 3, 8, 22, 93 };
    print_array(a, SIZE);
    insertion_sort(a, SIZE);
    print_array(a, SIZE);

    return 0;
}
