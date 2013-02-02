#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "util.h"

#define INF INT32_MAX

/* a[p..q..r] : a[p..q], a[q+1..r]
 * p start (left)
 * q middle (end of left)
 * q+1 (start of right)
 * r end (end of right)
 */
void
merge(int *a, int p, int q, int r)
{
    int i, j, k;
    int *left, *right;
    int n1 = q - p + 1;
    int n2 = r - q;

    left = malloc(sizeof (int) * (n1 + 1));
    right = malloc(sizeof (int) * (n2 + 1));
    assert(left && right);
    for (i = 0; i < n1; i++)
        left[i] = a[p + i];
    for (j = 0; j < n2; j++)
        right[j] = a[q + 1 + j];

    /* make 'for loop' below easy
     * about not crossing end of array
     * of left and right */
    left[n1] = INF;
    right[n2] = INF;
    i = 0;
    j = 0;
    for (k = p; k <= r; k++) {
        if (left[i] <= right[j]) {
            a[k] = left[i];
            i++;
        } else {
            a[k] = right[j];
            j++;
        }
    }
    assert(r - p + 1 == i + j);

    free(left);
    free(right);
}

/* p start
 * q end (not count)
 */
void
merge_sort(int *a, int p, int r)
{
    if (p < r) {
        int q = (p + r) / 2;
        merge_sort(a, p, q);
        merge_sort(a, q + 1, r);
        merge(a, p, q, r);
    }
}

void
main()
{
    /* Array of integers */
    int *a;
    int n;
    input(&a, &n);
    merge_sort(a, 0, n - 1);
    output(a, n);
}
