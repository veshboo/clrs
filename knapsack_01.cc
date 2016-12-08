#include <iostream>
#include <algorithm>
using namespace std;

int KnapsackAux(int n, int wt[], int vt[], int w, int **cache) {
    if (n == 0 || w == 0)
        return cache[n][w] = 0;
    if (cache[n][w] >= 0)
        return cache[n][w];

    if (w < wt[n-1])
        cache[n][w] = KnapsackAux(n-1, wt, vt, w, cache);
    else
        cache[n][w] = max(KnapsackAux(n-1, wt, vt, w - wt[n-1], cache) + vt[n-1],
                          KnapsackAux(n-1, wt, vt, w, cache));

    return cache[n][w];
}

int Knapsack(int n, int wt[], int vt[], int w) {
    int **cache = new int *[n+1];
    for (int i = 0; i <= n; i++) {
        cache[i] = new int [w+1];
        for (int j = 0; j <= w; j++) {
            cache[i][j] = -1;
        }
    }

    int x = KnapsackAux(n, wt, vt, w, cache);

    for (int i = 0; i <= n; i++)
        delete [] cache[i];
    delete [] cache;
    return x;
}

int KnapsackDP(int n, int wt[], int vt[], int w) {
    int **T = new int *[n+1];
    for (int i = 0; i <= n; i++) {
        T[i] = new int [w+1];
        for (int j = 0; j <= w; j++) {
            T[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= w; j++) {
            if (j - wt[i-1] >= 0) {
                T[i][j] = max(T[i-1][j - wt[i-1]] + vt[i-1], T[i-1][j]);
            } else {
                T[i][j] = T[i-1][j];
            }
        }
    }
    int x = T[n][w];

    for (int i = 0; i <= n; i++)
        delete [] T[i];
    delete [] T;
    return x;
}

int main() {
    {
        int n = 3;
        int w = 50;
        int wt[] = {10, 20, 30};
        int vt[] = {60, 100, 120};
        cout << Knapsack(n, wt, vt, w) << endl;
        cout << KnapsackDP(n, wt, vt, w) << endl;
    }
    {
        int n = 5;
        int w = 15;
        int wt[] = {12, 2, 1, 4, 1};
        int vt[] = {4, 2, 1, 10, 2};
        cout << Knapsack(n, wt, vt, w) << endl;
        cout << KnapsackDP(n, wt, vt, w) << endl;
    }
    return 0;
}
