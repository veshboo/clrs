#include <stdio.h>

/* Correct to find out minimum value
 * but, useless smart or complex.
 * Divide & conquer is no big help
 * when dividing into sub problems
 * does not make the required time
 * to solve it `dramatically' lessen
 * against whole problem */

int
min(int *a, int p, int n)
{
    int left;
    int right;
    if (n == 1)
        return a[p];
    left = min(a, p, n/2);
    right = min(a, p + n/2, n - n/2);
    return (left < right)? left : right;
}

void
main()
{
    /* Array of integers */
    int *a;
    int n;
    int m;
    input(&a, &n);
    printf("Correct, but useless smart\n");
    m = min(a, 0, n);
    printf("minimum=%d\n", m);
}
