#include <stdio.h>
#include <iostream>
#include <random>
#include <numeric>

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
    swap(&arr[low], &arr[(low + (high - low) / 3)]);
    swap(&arr[high], &arr[(high - (high - low) / 3)]);
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
    std::random_device rd;                        // obtain a random number from hardware
    std::mt19937 gen(rd());                       // seed the generator
    std::uniform_int_distribution<> distr(1, 20); // define the range

    for (int i = 0; i < n; ++i)
        change_array[i] = distr(gen);
}

// Method for getting random array wtih n elements
void randomArrayDuplicates(int change_array[], int n)
{
    std::random_device rd;                        // obtain a random number from hardware
    std::mt19937 gen(rd());                       // seed the generator
    std::uniform_int_distribution<> distr(1, 20); // define the range

    for (int i = 0; i < n; ++i)
        if (i % 2 == 0)
            change_array[i] = distr(gen);
        else
            change_array[i] = 4;
}

void sortedArray(int change_array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        change_array[i] = i;
    }
}

// Finds the combined value of the elements inside an array
int checksum(int *arr, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum;
}

bool correctOrder(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i + 1] < arr[i])
        {
            return false;
        }
    }
    return true;
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

    std::cout << "\n size: " << *(&testArray1 + 1) - testArray1;

    int checksum1 = checksum(testArray1, (*(&testArray1 + 1) - testArray1));
    int checksum2 = checksum(testArray2, (*(&testArray2 + 1) - testArray2));
    bool firstOrder1 = correctOrder(testArray1, (*(&testArray1 + 1) - testArray1));
    bool firstOrder2 = correctOrder(testArray2, (*(&testArray2 + 1) - testArray2));

    quicksort1(testArray1, 0, (*(&testArray1 + 1) - testArray1) - 1);
    DualPivotQuickSort(testArray2, 0, (*(&testArray2 + 1) - testArray2) - 1);

    std::cout
        << "\n checksum before: " << checksum1
        << "\n checksum after: " << checksum(testArray1, (*(&testArray1 + 1) - testArray1))
        << "\n correct order before? " << firstOrder1
        << "\n correct order after? " << correctOrder(testArray1, (*(&testArray1 + 1) - testArray1))
        << "\n Test array after single pivot quicksort:\n";

    for (int i = 0; i < 10; i++)
    {
        std::cout << testArray1[i] << ", ";
    }

    std::cout
        << "\n checksum before: " << checksum2
        << "\n checksum after: " << checksum(testArray2, (*(&testArray2 + 1) - testArray2))
        << "\n correct order before? " << firstOrder2
        << "\n correct order after? " << correctOrder(testArray2, (*(&testArray2 + 1) - testArray2))
        << "\n Test array after dual pivot quicksort:\n";

    for (int i = 0; i < 10; i++)
    {
        std::cout << testArray2[i] << ", ";
    }
    std::cout << "\n";

    // Test loops
    int sizes[] = {pow(10, 5), pow(10, 6), pow(10, 7), pow(10, 8)};
    /*
    for (int i = 0; i < 4; i++)
    {
        // Random data
        // Test data
        int *randArray1 = new int[sizes[i]];
        randomArray(randArray1, sizes[i]);
        int *randArray2 = new int[sizes[i]];
        randomArray(randArray2, sizes[i]);
        int checksum1 = checksum(randArray1, sizes[i]);
        int checksum2 = checksum(randArray2, sizes[i]);
        bool rightOrder1 = correctOrder(randArray1, sizes[i]);
        bool rightOrder2 = correctOrder(randArray2, sizes[i]);

        // Get starting timepoint
        std::chrono::steady_clock::time_point begin221 = std::chrono::steady_clock::now();

        quicksort1(randArray1, 0, sizes[i] - 1);

        // Get ending timepoint
        std::chrono::steady_clock::time_point end221 = std::chrono::steady_clock::now();
        long duration221 = std::chrono::duration_cast<std::chrono::microseconds>(end221 - begin221).count();

        std::cout << "\n Single Pivot "
                  << " Array with "
                  << sizes[i] << "  random elements\n"
                  << "\nsum before: " << checksum1
                  << "\nsum after: " << checksum(randArray1, sizes[i])
                  << "\ncorrect order before? " << rightOrder1
                  << "\ncorrect order after? " << correctOrder(randArray1, sizes[i])
                  << "\n\nDuration of function: " << duration221 << "[µs]"
                  << std::endl;

        // Get starting timepoint
        std::chrono::steady_clock::time_point begin233 = std::chrono::steady_clock::now();

        DualPivotQuickSort(randArray2, 0, sizes[i] - 1);

        // Get ending timepoint
        std::chrono::steady_clock::time_point end233 = std::chrono::steady_clock::now();
        long duration233 = std::chrono::duration_cast<std::chrono::microseconds>(end233 - begin233).count();

        std::cout << "\n Dual Pivot "
                  << " Array with "
                  << sizes[i] << "  random elements\n"
                  << "\nsum before: " << checksum2
                  << "\nsum after: " << checksum(randArray2, sizes[i])
                  << "\ncorrect order before? " << rightOrder2
                  << "\ncorrect order after? " << correctOrder(randArray2, sizes[i])
                  << "\n\nDuration of function: " << duration233 << "[µs]"
                  << std::endl;
    }

    /*

        // Random data with duplicates
        // Test data
        int *randArray1 = new int[sizes[i]];
        randomArrayDuplicates(randArray1, sizes[i]);
        int *randArray2 = new int[sizes[i]];
        randomArrayDuplicates(randArray2, sizes[i]);
        int checksum1 = checksum(randArray1, sizes[i]);
        int checksum2 = checksum(randArray2, sizes[i]);
        bool rightOrder1 = correctOrder(randArray1, sizes[i]);
        bool rightOrder2 = correctOrder(randArray2, sizes[i]);

        std::cout << "\n first elements of array with duplicates: \n";
        for (int k = 0; k < 10; k++)
        {
            std::cout << randArray2[k] << ", ";
        }

        // Get starting timepoint
        std::chrono::steady_clock::time_point begin221 = std::chrono::steady_clock::now();

        quicksort1(randArray1, 0, sizes[i] - 1);

        // Get ending timepoint
        std::chrono::steady_clock::time_point end221 = std::chrono::steady_clock::now();
        long duration221 = std::chrono::duration_cast<std::chrono::microseconds>(end221 - begin221).count();

        std::cout << "\nSingle Pivot "
                  << " Array with "
                  << sizes[i] << "  random elements with duplicates\n"
                  << "\nsum before: " << checksum1
                  << "\nsum after: " << checksum(randArray1, sizes[i])
                  << "\ncorrect order before? " << rightOrder1
                  << "\ncorrect order after? " << correctOrder(randArray1, sizes[i])
                  << "\n\nDuration of function: " << duration221 << "[µs]"
                  << std::endl;

        // Get starting timepoint
        std::chrono::steady_clock::time_point begin233 = std::chrono::steady_clock::now();

        DualPivotQuickSort(randArray2, 0, sizes[i] - 1);

        // Get ending timepoint
        std::chrono::steady_clock::time_point end233 = std::chrono::steady_clock::now();
        long duration233 = std::chrono::duration_cast<std::chrono::microseconds>(end233 - begin233).count();

        std::cout << "\nDual Pivot "
                  << " Array with "
                  << sizes[i] << "  random elements with duplicates\n"
                  << "\nsum before: " << checksum2
                  << "\nsum after: " << checksum(randArray2, sizes[i])
                  << "\ncorrect order before? " << rightOrder2
                  << "\ncorrect order after? " << correctOrder(randArray2, sizes[i])
                  << "\n\nDuration of function: " << duration233 << "[µs]"
                  << std::endl;
    }
    */

    /*

        // Sorted data
        // Test data
        int *randArray1 = new int[sizes[i]];
        sortedArray(randArray1, sizes[i]);
        int *randArray2 = new int[sizes[i]];
        sortedArray(randArray2, sizes[i]);
        int checksum1 = checksum(randArray1, sizes[i]);
        int checksum2 = checksum(randArray2, sizes[i]);
        bool rightOrder1 = correctOrder(randArray1, sizes[i]);
        bool rightOrder2 = correctOrder(randArray2, sizes[i]);

        std::cout << "\n first elements of sorted array: \n";
        for (int k = 0; k < 10; k++)
        {
            std::cout << randArray2[k] << ", ";
        }

        // Get starting timepoint
        std::chrono::steady_clock::time_point begin221 = std::chrono::steady_clock::now();

        quicksort1(randArray1, 0, sizes[i] - 1);

        // Get ending timepoint
        std::chrono::steady_clock::time_point end221 = std::chrono::steady_clock::now();
        long duration221 = std::chrono::duration_cast<std::chrono::microseconds>(end221 - begin221).count();

        std::cout << "\nSingle Pivot "
                  << " Array with "
                  << sizes[i] << "  random elements with duplicates\n"
                  << "\nsum before: " << checksum1
                  << "\nsum after: " << checksum(randArray1, sizes[i])
                  << "\ncorrect order before? " << rightOrder1
                  << "\ncorrect order after? " << correctOrder(randArray1, sizes[i])
                  << "\n\nDuration of function: " << duration221 << "[µs]"
                  << std::endl;

        // Get starting timepoint
        std::chrono::steady_clock::time_point begin233 = std::chrono::steady_clock::now();

        DualPivotQuickSort(randArray2, 0, sizes[i] - 1);

        // Get ending timepoint
        std::chrono::steady_clock::time_point end233 = std::chrono::steady_clock::now();
        long duration233 = std::chrono::duration_cast<std::chrono::microseconds>(end233 - begin233).count();

        std::cout << "\nDual Pivot "
                  << " Array with "
                  << sizes[i] << "  random elements with duplicates\n"
                  << "\nsum before: " << checksum2
                  << "\nsum after: " << checksum(randArray2, sizes[i])
                  << "\ncorrect order before? " << rightOrder2
                  << "\ncorrect order after? " << correctOrder(randArray2, sizes[i])
                  << "\n\nDuration of function: " << duration233 << "[µs]"
                  << std::endl;
    }
    */

    return 0;
}
