#include <stdio.h>
#include <iostream>
#include <random>

/*
    Single pivot quicksort
*/

// Swap two values
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int median3sort(int *t, int v, int h)
{
    int m = (v + h) / 2;
    if (t[v] > t[m])
        swap(&t[v], &t[m]);
    if (t[m] > t[h])
    {
        swap(&t[m], &t[h]);
        if (t[v] > t[m])
            swap(&t[v], &t[m]);
    }
    return m;
}

int splitt(int *t, int v, int h)
{
    int iv, ih;
    int m = median3sort(t, v, h);
    int dv = t[m];
    swap(&t[m], &t[h - 1]);
    for (iv = v, ih = h - 1;;)
    {
        while (t[++iv] < dv)
            ;
        while (t[--ih] > dv)
            ;
        if (iv >= ih)
            break;
        swap(&t[iv], &t[ih]);
    }
    swap(&t[iv], &t[h - 1]);
    return iv;
}

// Method implementing quicksort with single pivot
void quicksort1(int *t, int v, int h)
{
    if (h - v > 2)
    {
        int delepos = splitt(t, v, h);
        quicksort1(t, v, delepos - 1);
        quicksort1(t, delepos + 1, h);
    }
    else
        median3sort(t, v, h);
}

/*
    Dual pivot quicksort
*/

int partition(int *arr, int low, int high, int *lp)
{
    if (arr[low] > arr[high])
        swap(&arr[low], &arr[high]);

    // p is the left pivot, and q is the right pivot.
    int j = low + 1;
    int g = high - 1, k = low + 1, p = arr[low], q = arr[high];
    while (k <= g)
    {

        // if elements are less than the left pivot
        if (arr[k] < p)
        {
            swap(&arr[k], &arr[j]);
            j++;
        }

        // if elements are greater than or equal
        // to the right pivot
        else if (arr[k] >= q)
        {
            while (arr[g] > q && k < g)
                g--;
            swap(&arr[k], &arr[g]);
            g--;
            if (arr[k] < p)
            {
                swap(&arr[k], &arr[j]);
                j++;
            }
        }
        k++;
    }
    j--;
    g++;

    // bring pivots to their appropriate positions.
    swap(&arr[low], &arr[j]);
    swap(&arr[high], &arr[g]);

    // returning the indices of the pivots.
    *lp = j; // because we cannot return two elements
    // from a function.

    return g;
}

void DualPivotQuickSort(int *arr, int low, int high)
{
    if (low < high)
    {
        // lp means left pivot, and rp means right pivot.
        int lp, rp;
        rp = partition(arr, low, high, &lp);
        DualPivotQuickSort(arr, low, lp - 1);
        DualPivotQuickSort(arr, lp + 1, rp - 1);
        DualPivotQuickSort(arr, rp + 1, high);
    }
}

// Method for getting random array wtih n elements
void randomArray(int change_array[], int n)
{
    std::random_device rd;                          // obtain a random number from hardware
    std::mt19937 gen(rd());                         // seed the generator
    std::uniform_int_distribution<> distr(-10, 10); // define the range

    for (int i = 0; i < n; ++i)
        change_array[i] = distr(gen);
}

int main(void)
{
    // Test data
    int testArray1[10] = {0, 2, 9, 3, 8, 4, 7, 5, 6, 1};
    int testArray2[10] = {0, 2, 9, 3, 8, 4, 7, 5, 6, 1};
    std::cout << "Test array:\n";
    for (int i = 0; i < 10; i++)
    {
        std::cout << testArray1[i] << ", ";
    }

    quicksort1(testArray1, 0, 9);
    DualPivotQuickSort(testArray2, 0, 9);

    std::cout
        << "\n Test array after single pivot quicksort:\n";

    for (int i = 0; i < 10; i++)
    {
        std::cout << testArray1[i] << ", ";
    }

    std::cout
        << "\n Test array after dual pivot quicksort:\n";

    for (int i = 0; i < 10; i++)
    {
        std::cout << testArray2[i] << ", ";
    }

    return 0;
}
