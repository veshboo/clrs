#include <stdio.h>
#include "util.h"
#include "heap.h"

void
main()
{
    /* Array of integers */
    int *a;
    int n;

    input(&a, &n);
    heapsort(a, n);
    output(a, n);
}
