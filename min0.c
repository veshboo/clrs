#include <stdio.h>

int
min(int *a, int p, int n)
{
  int i;
  int m;

  m = a[p];
  for (i = p + 1; i < n; i++) {
    if (a[i] < m)
      m = a[i];
  }
  return m;
}

void
main()
{
    /* Array of integers */
    int *a;
    int n;
    int m;
    input(&a, &n);
    printf("Brute-froce, linear search\n");
    m = min(a, 0, n);
    printf("minimum=%d\n", m);
}
