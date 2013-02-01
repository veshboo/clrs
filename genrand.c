#include <stdio.h>

void
usage()
{
  printf("Usage: genrand count max\n");
  printf(" count  Number of random numbers to generate\n");
  printf(" max    Max value of random number. (i.e, 1...max)\n");
}

void
main(int argc, char *argv[])
{
  int i = 0;
  int count;
  int max;

  if (argc != 3) {
    printf("Error: invalid number of arguments\n");
    usage();
    return;
  }
  count = atoi(argv[1]);
  max = atoi(argv[2]);
  if (!count || !max) {
    printf("Error: count or max value is zero\n");
    usage();
    return;
  }
  
  while (i++ < count) {
    long int n = random() % max;
    printf("%d\n", (int) n);
  }
}
