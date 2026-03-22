#include "sorting.h"


/// COMPARISONS

void shellSort(int a[], int n, long long& comparisons) {
    comparisons = 0;
    for (int gap = n / 2; ++comparisons && gap > 0; gap /= 2) {
        for (int i = gap; ++comparisons && i < n; i++) {
            int x = a[i];
            int j = i;
            while (++comparisons && j >= gap) {
                comparisons++; // Đếm a[j - gap] > x
                if (a[j - gap] > x) {
                    a[j] = a[j - gap];
                    j -= gap;
                }
                else break;
            }
            a[j] = x;
        }
    }
}

int partition(int a[], int l, int r, long long &comparisons) {
    int pivot = a[r];
    int i = l - 1;
    for (int j = l; ++comparisons && j < r; j++) {
        comparisons++; // Đếm a[j] < pivot
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[r]);
    return i + 1;
}

void quickSort(int a[], int l, int r, long long &comparisons) {
    if (++comparisons && l < r) {
        int pivotIndex = l + rand() % (r - l + 1);
        swap(a[pivotIndex], a[r]);
        int p = partition(a, l, r, comparisons);
        quickSort(a, l, p - 1, comparisons);
        quickSort(a, p + 1, r, comparisons);
    }
}

void merge(int a[], int l, int m, int r, long long &comparisons) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int* L = new int[n1];
    int* R = new int[n2];
    for (int i = 0; ++comparisons && i < n1; i++) L[i] = a[l + i];
    for (int j = 0; ++comparisons && j < n2; j++) R[j] = a[m + 1 + j];

    int i = 0, j = 0, k = l;
    while ((++comparisons && i < n1) && (++comparisons && j < n2)) {
        comparisons++; // Đếm L[i] <= R[j]
        if (L[i] <= R[j]) a[k++] = L[i++];
        else a[k++] = R[j++];
    }
    while (++comparisons && i < n1) a[k++] = L[i++];
    while (++comparisons && j < n2) a[k++] = R[j++];
    delete[] L; delete[] R;
}

void mergeSort(int a[], int l, int r, long long &comparisons) {
    if (++comparisons && l < r) {
        int m = l + (r - l) / 2;
        mergeSort(a, l, m, comparisons);
        mergeSort(a, m + 1, r, comparisons);
        merge(a, l, m, r, comparisons);
    }
}

void maxHeapify(int a[], int n, int i, long long& comparisons) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (++comparisons && l < n) {
        comparisons++; // Đếm a[l] > a[largest]
        if (a[l] > a[largest]) largest = l;
    }
    if (++comparisons && r < n) {
        comparisons++; // Đếm a[r] > a[largest]
        if (a[r] > a[largest]) largest = r;
    }
    if (++comparisons && largest != i) {
        swap(a[i], a[largest]);
        maxHeapify(a, n, largest, comparisons);
    }
}

void heapSort(int a[], int n, long long& comparisons) {
    comparisons = 0;
    for (int i = n / 2 - 1; ++comparisons && i >= 0; i--)
        maxHeapify(a, n, i, comparisons);
    for (int i = n - 1; ++comparisons && i > 0; i--) {
        swap(a[0], a[i]);
        maxHeapify(a, i, 0, comparisons);
    }
}

///---------------------------------------------------
/// NO COMPARISONS

void shellSort(int a[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int x = a[i];
            int j = i;
            while (j >= gap && a[j - gap] > x) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = x;
        }
    }
}

int partitionSimple(int a[], int l, int r) {
    int pivot = a[r];
    int i = l - 1;
    for (int j = l; j < r; j++) {
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[r]);
    return i + 1;
}

void quickSort(int a[], int l, int r) {
    if (l < r) {
        int pivotIndex = l + rand() % (r - l + 1);
        swap(a[pivotIndex], a[r]);
        int p = partitionSimple(a, l, r);
        quickSort(a, l, p - 1);
        quickSort(a, p + 1, r);
    }
}

void merge(int a[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int* L = new int[n1];
    int* R = new int[n2];
    for (int i = 0; i < n1; i++) L[i] = a[l + i];
    for (int j = 0; j < n2; j++) R[j] = a[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) a[k++] = L[i++];
        else a[k++] = R[j++];
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
    delete[] L; delete[] R;
}

void mergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

void maxHeapify(int a[], int n, int i) {
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && a[l] > a[largest]) largest = l;
    if (r < n && a[r] > a[largest]) largest = r;
    if (largest != i) {
        swap(a[i], a[largest]);
        maxHeapify(a, n, largest);
    }
}

void heapSort(int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) maxHeapify(a, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        maxHeapify(a, i, 0);
    }
}


// Thêm vào cuối file efficient_sorts.cpp
void quickSort(int a[], int n, long long &comparisons) {
    comparisons = 0; 
    quickSort(a, 0, n - 1, comparisons);
}

void mergeSort(int a[], int n, long long &comparisons) {
    comparisons = 0; 
    mergeSort(a, 0, n - 1, comparisons);

}
void quickSort(int a[], int n) {
    quickSort(a, 0, n - 1);
}
void mergeSort(int a[], int n) {
    mergeSort(a, 0, n - 1);
}