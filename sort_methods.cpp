#include "sort_methods.h"
#include <iostream>
#include <algorithm>

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

// сортировка быстрая с выбором последнего элемента
int quick_sorted(int *v, int l, int r) {
    int q = v[(l + r) / 2];
    int i = l;
    int j = r;
    while (i <= j) {
        while (v[i] < q)
            i++;
        while (v[j] > q)
            j--;
        if (i >= j)
            break;
        swap(v[i++], v[j--]);
    }
    return j;
}
void quick_sort(int *v, int l, int r) {
    if (r <= l)
        return;
    int q = quick_sorted(v, l, r);
    quick_sort(v, l, q);
    quick_sort(v, q + 1, r);
} 

// сортировка выбором
void selection_sort(int *v, int n) {
    for (int i = 0; i < n; i++) {
        int min = v[i];
        for (int j = i + 1; j < n; j++) {
            if (min > v[j]) {
                min = v[j];
            }
        }
        swap(v[i], min);
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
