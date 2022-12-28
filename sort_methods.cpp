#include "sort_methods.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

// печатать список
void print_array(const int *v, int n) {
    for (int i = 0; i < n; i++)
        cout << v[i] << " ";
    cout << "\n";
}

// сортировка встроенная sort
void built_in_sort(int *v, int n) {
    sort(v, v + n);
} 

// сортировка встроенная stable_sort
void built_in_stable_sort(int *v, int n) {
    stable_sort(v, v + n);
} 

// пузырьковая сортировка
void bubble_sort(int *v, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

// пузырьковая сортировка с выходом по условию 
// отсутствия обменов на очередном проходе
void bubble_sort_opt(int *v, int n) {
    for (int i = 1; i < n; i++) {
        bool done = true;
        for (int j = 0; j < n - i; j++) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
                done = false;
            }
        }
        if (done) {
            break;
        }
    }
}

// сортировка слиянием;
void merge_sorted(int *v, int last1, int last2) {
    int *result = new int[last2];
    int i = 0;
    int j = last1;
    int k = 0;
    while (i < last1 && j < last2) {
        if (v[i] < v[j]) {
            result[k++] = v[i];
            i++;
        }
        else {
            result[k++] = v[j];
            j++;
        }
    }
    if (i == last1) {
        while (j < last2) {
            result[k++] = v[j++];
        }
    }
    else if (j == last2) {
        while (i < last1) {
            result[k++] = v[i++];
        }
    }
    for (k = 0; k < last2; k++) {
        v[k] = result[k];
    }
    delete[] result;
}
void merge_sort(int *v, int size) {
    if (size <= 1) {
        return;
    }
    merge_sort(v, size / 2);
    merge_sort(v + size / 2, size - size / 2);
    merge_sorted(v, size / 2, size);
} 

// сортировка быстрая с выбором среднего элемента
int partion(int *v, int l, int r, bool use_median_of_fml_instead_of_middle = false) {
    if (l >= r || l < 0) {
        return r;
    }
    int pivot_ind = (l + r) / 2;
    if (use_median_of_fml_instead_of_middle) {
        int a[] = {v[l], v[(l + r) / 2], v[r]};
        sort(a, a + 3);
        int median = a[1];
        if (median == v[l])
            pivot_ind = l;
        else if (median == v[r])
            pivot_ind = r;
    }
    int pivot = v[pivot_ind];
    swap(v[r], v[pivot_ind]);

    int i = l - 1;
    for (int j = l; j < r; j++) { 
        if (v[j] <= pivot) {
            i++;
            swap(v[i], v[j]);
        }
    }
    i++;
    swap(v[i], v[r]);
    return i;
}

void quick_sort(int *v, int n) {
    if (n <= 1)
        return;
    int q = partion(v, 0, n - 1);
    quick_sort(v, q);
    quick_sort(v + q + 1, n - q - 1);
} 

void quick_sort_fml(int *v, int n) {
    if (n <= 1)
        return;
    int q = partion(v, 0, n - 1, true);
    quick_sort(v, q);
    quick_sort(v + q + 1, n - q - 1);
} 

// сортировка выбором
void selection_sort(int *v, int n) {
    for (int i = 0; i < n; i++) {
        int min = v[i];
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (min > v[j]) {
                min = v[j];
                min_idx = j;
            }
        }
        swap(v[i], v[min_idx]);
    }
}

// сортировка вставками
void insertion_sort(int *v, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && v[j - 1] > v[j]; j--) {
            swap(v[j - 1], v[j]); 
        }
    }  
}

// сортировка кучей
void heap_sort(int *v, int n) {
    priority_queue<int> pq;
    for (int i = 0; i < n; i++) {
        pq.push(v[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        v[i] = pq.top();
        pq.pop();
    }
}