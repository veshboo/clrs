#include <stdio.h>
#include "util.h"

void
insertion_sort(int *a, int n)
{
  int i, j, key;

  for (j = 1; j < n; j++) {
    key = a[j];
    /* insert a[j] into the sorted sequence A[0..j-1] */
    i = j - 1;
    while (i >= 0 && a[i] > key) {
      a[i + 1] = a[i];
      i--;
    }
    a[i + 1] = key;
  }
}

void
main()
{
    /* Array of integers */
    int *a;
    int n;

    input(&a, &n);
    insertion_sort(a, n);
    output(a, n);
}
