#include <stdio.h>
#include <stdlib.h>

/* Read number of integers from stdin */
void
input(int **a, int *n)
{
  int sz = 0;
  *a = NULL;
  *n = 0;
  while (!feof(stdin)) {
    if ((*n) >= sz) {
      sz += 4096;
      *a = realloc(*a, sz * sizeof (int));
    }
    scanf("%d\n", (*a) + (*n));
    (*n)++;
  }
}

/* Write out to stdout */
void
output(int *a, int n)
{
  int i;
  for (i = 0; i < n; i++)
    printf("%d\n", a[i]);
}
