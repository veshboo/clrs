#include "heap.h"

/* sub tree rooted at element i
 * make it hold max heap property */
void
max_heapify(int *a, int n, int i)
{
    int l, r;
    int largest;
    l = left(i);
    r = right(i);
    if (l < n && a[l] > a[i])
        largest = l;
    else
        largest = i;
    if (r < n && a[r] > a[largest])
        largest = r;
    if (largest != i) {
        int tmp;
        tmp = a[i];
        a[i] = a[largest];
        a[largest] = tmp;
        max_heapify(a, n, largest);
    }
}

/* max heapify for all non-leaf nodes
 * is building max heap */
void
build_max_heap(int *a, int n)
{
    int i;
    for (i = n/2 - 1; i >= 0; i--)
        max_heapify(a, n, i);
}

/* heapsort
 * start by building max heap
 * repeat to remove a[0] maximum
 * and max-heapify.
 * exchange with last element
 * is non-trivial trick for in-place sort.
 *
 * Overall, we get from maximum to minimum
 * from heap, and put maximum to last
 * and minimum to first.
 * resulting sort is increase order.
 *
 * for loop below build-max-heap run
 * at O(n*lg(n)) */
void
heapsort(int *a, int n)
{
    int i;
    build_max_heap(a, n);
    for (i = n - 1; i >= 1; i--) {
        int tmp;
        tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;
        n--;
        max_heapify(a, n, 0);
    }
}

