#ifndef _HEAP_H_
#define _HEAP_H_

/*                 0
 *           1           2
 *        3     4     5     6
 *       7 8   9 10 11 12 13 14
 */

static inline int
parent(int i)
{
    return (i-1)/2;
}

static inline int
left(int i)
{
    return 2*i + 1;
}

static inline int
right(int i)
{
    return 2*i + 2;
}

extern void max_heapify(int *a, int n, int i);
extern void build_max_heap(int *a, int n);

#endif /* !_HEAP_H_ */
