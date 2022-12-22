#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include <vector>
#include "sort_methods.h"

using namespace std;

enum ArrayType {randomized = 0, sorted, inversed, nearly_sorted, array_types_num};
string types_names[] = {"randomized", "sorted", "inversed", "nearly_sorted"};

typedef void (*sort_method_ptr)(int *, int);
vector<sort_method_ptr> sort_methods = {bubble_sort, bubble_sort_opt, built_in_sort, built_in_stable_sort, merge_sort, selection_sort, insertion_sort, quick_sort};
string methods_names[] = {"bubble_sort", "bubble_sort_opt", "built_in_sort", "built_in_stable_sort", "merge_sort", "selection_sort", "insertion_sort", "quick_sort"};

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

double test_sort_method(int n, sort_method_ptr sort_method, ArrayType t) {
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
    int m = 0;
    for (auto sort_method: sort_methods) {
        int n = 100; 
        cout << methods_names[m++] << ":\n";
        for (int t = randomized; t < array_types_num; t++) {
            double total_time = 0;
            for (int i = 0; i < TRIALS_NUM; i++) {
                total_time += test_sort_method(n, sort_method, static_cast<ArrayType>(t));
            }
            total_time /= TRIALS_NUM;
            cout << "total_time " << types_names[t] << ": " << total_time << "\n";
        }
        cout << "\n";
    }
    return 0;
}