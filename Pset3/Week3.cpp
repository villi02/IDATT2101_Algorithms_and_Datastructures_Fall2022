#include <stdio.h>

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

// Swap two values
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int main()
{
    
}
