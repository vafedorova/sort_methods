#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include "sort_methods.h"

using namespace std;

enum ArrayType {randomized, sorted, inversed, nearly_sorted};
string types_names[4] = {"randomized", "sorted", "inversed", "nearly_sorted"};

void generate_array(int *v, int n, int rand_max, ArrayType t) {
    for (int i = 0; i < n; i++) {
        v[i] = rand() % rand_max;
    }
    switch (t)
    {
    case sorted:
        sort(v, v + n);
        break;
    case inversed:
        sort(v, v + n);
        reverse(v, v + n);
        break;
    case nearly_sorted:
        {
        sort(v, v + n);
        int k = n / 10;
        for (int i = 0; i < k; i++) {
            v[rand() % n] = rand() % rand_max;
        }
        break;
        }
    default:
        break;
    }
}

double test_sort_method(int n, void (*sort_method)(int *, int), ArrayType t) {
    int *v = new int[n];
    generate_array(v, n, 2 * n, t);
    double ticks_start = clock();
    sort_method(v, n);
    double time_used = (clock() - ticks_start) / (double)CLOCKS_PER_SEC;
    delete[] v;
    return time_used;
}

const int TRIALS_NUM = 100;
int main() {
    srand(time(0));
    int n = 1000; 
    for (int t = 0; t < 4; t++) {
        double total_time = 0;
        for (int i = 0; i < TRIALS_NUM; i++) {
            total_time += test_sort_method(n, selection_sort, static_cast<ArrayType>(t));
        }
        total_time /= TRIALS_NUM;
        cout << "total_time " << types_names[t] << ": " << total_time << "\n";
    }
    return 0;
}