#include <iostream>
#include <vector>
using namespace std;

void Exchange(int *A, int i, int j) {
    if (i != j) {
        int t = A[i];
        A[i] = A[j];
        A[j] = t;
    }
}

// A[p..r], p <= r
// pick q, p <= q <=r, partition to have, A[p..q-1] <= A[q] <= A[q+1..r]
// return q
int Partition(int *A, int p, int r) {
    int x = A[r]; // pivot value, just use last value
    int i = p - 1; // end index of left (less or eq to pivot value)
    for (int j = p; j <= r - 1; j++) {
        if (A[j] <= x) Exchange(A, ++i, j);
    }
    Exchange(A, ++i, r); // r == j
    return i;
}

// A[p..r], p and r is start/end index
void QuickSort(int *A, int p, int r) {
    if (p < r) {
        int q = Partition(A, p, r);
        QuickSort(A, p, q - 1);
        QuickSort(A, q + 1, r);
    }
}

int main(void) {
    vector<int> A;
    int n;
    while (true) {
        int a;
        cin >> a;
        if (cin.eof())
            break;
        A.push_back(a);

    }
    n = A.size();

    QuickSort(A.data(), 0, n - 1);

    for (int i = 0; i < n; i++)
        cout << A[i] << endl;
    return 0;
}
