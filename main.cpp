#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include <vector>
#include "sort_methods.h"

using namespace std;

enum ArrayType {randomized = 0, sorted, inversed, nearly_sorted, array_types_num};
string types_names[] = {"randomized", "sorted", "inversed", "nearly_sorted"};

typedef void (*sort_method_ptr_sqrt)(int *, int);
vector<sort_method_ptr_sqrt> sort_methods_sqrt = {bubble_sort, bubble_sort_opt, selection_sort, insertion_sort};
string methods_names_sqrt[] = {"bubble_sort", "bubble_sort_opt", "selection_sort", "insertion_sort"};

typedef void (*sort_method_ptr_log)(int *, int);
vector<sort_method_ptr_log> sort_methods_log = {built_in_sort, built_in_stable_sort, merge_sort, quick_sort, heap_sort};
string methods_names_log[] = {"built_in_sort", "built_in_stable_sort", "merge_sort", "quick_sort", "heap_sort"};

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

double test_sort_method_sqrt(int n, sort_method_ptr_sqrt sort_method_sqrt, ArrayType t) {
    int *v = new int[n];
    generate_array(v, n, 2 * n, t);
    print_array(v, n);
    double ticks_start = clock();
    sort_method_sqrt(v, n);
    print_array(v, n);
    double time_used = (clock() - ticks_start) / (double)CLOCKS_PER_SEC;
    delete[] v;
    return time_used;
}

double test_sort_method_log(int n, sort_method_ptr_log sort_method_log, ArrayType k) {
    int *v = new int[n];
    generate_array(v, n, 2 * n, k);
    print_array(v, n);
    double ticks_start = clock();
    sort_method_log(v, n);
    print_array(v, n);
    double time_used = (clock() - ticks_start) / (double)CLOCKS_PER_SEC;
    delete[] v;
    return time_used;
}

const int TRIALS_NUM = 2;
int main() {
    srand(time(0));
    int m = 0;
    for (auto sort_method_sqrt: sort_methods_sqrt) {
        int n = 10; 
        cout << methods_names_sqrt[m++] << ":\n";
        for (int t = randomized; t < array_types_num; t++) {
            double total_time = 0;
            for (int i = 0; i < TRIALS_NUM; i++) {
                total_time += test_sort_method_sqrt(n, sort_method_sqrt, static_cast<ArrayType>(t));
            }
            total_time /= TRIALS_NUM;
            cout << "total_time " << types_names[t] << ": " << total_time << "\n";
        }
        cout << "\n";
    }
    for (auto sort_method_log: sort_methods_log) {
        m = 0;
        int n = 10;
        cout << methods_names_log[m++] << ":\n";
        for (int k = randomized; k < array_types_num; k++) {
            double total_time = 0;
            for (int i = 0; i < TRIALS_NUM; i++) {
                total_time += test_sort_method_log(n, sort_method_log, static_cast<ArrayType>(k));
            }
            total_time /= TRIALS_NUM;
            cout << "total_time " << types_names[k] << ": " << total_time << "\n";
        }
        cout << "\n";
    }
    return 0;
}