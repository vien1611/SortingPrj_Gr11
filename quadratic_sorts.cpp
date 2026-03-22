#include "sorting.h"


///COMPARISONS


void selectionSort(int a[], int n, long long& comparisons) {
    comparisons = 0;
    for (int i = 0; ++comparisons && i < n - 1; i++) {
        int minidx = i;
        for (int j = i + 1; ++comparisons && j < n; j++) {
            if (++comparisons && a[j] < a[minidx]) minidx = j;
        }
        swap(a[i], a[minidx]);
    }
}

void bubbleSort(int a[], int n, long long& comparisons) {
    comparisons = 0;
    for (int i = 0; ++comparisons && i < n - 1; i++) {
        for (int j = 0; ++comparisons && j < n - i - 1; j++) {
            if (++comparisons && a[j] > a[j + 1]) swap(a[j], a[j + 1]);
        }
    }
}

void insertionSort(int a[], int n, long long& comparisons) {
    comparisons = 0;
    for (int i = 1; ++comparisons && i < n; i++) {
        int x = a[i], j = i - 1;
        while (++comparisons && j >= 0) {
            if (++comparisons && a[j] > x) {
                a[j + 1] = a[j];
                j--;
            } else break;
        }
        a[j + 1] = x;
    }
}

void binaryInsertionSort(int a[], int n, long long& comparisons) {
    comparisons = 0;
    for (int i = 1; ++comparisons && i < n; i++) {
        int x = a[i], left = 0, right = i - 1;
        while (++comparisons && left <= right) {
            int mid = left + (right - left) / 2;
            if (++comparisons && a[mid] > x) right = mid - 1;
            else left = mid + 1;
        }
        for (int j = i - 1; ++comparisons && j >= left; j--) a[j + 1] = a[j];
        a[left] = x;
    }
}

void shakerSort(int a[], int n, long long& comparisons) {
    comparisons = 0;
    int left = 0, right = n - 1;
    while (++comparisons && left < right) {
        for (int i = left; ++comparisons && i < right; i++) {
            if (++comparisons && a[i] > a[i + 1]) swap(a[i], a[i + 1]);
        }
        right--;
        for (int i = right; ++comparisons && i > left; i--) {
            if (++comparisons && a[i] < a[i - 1]) swap(a[i], a[i - 1]);
        }
        left++;
    }
}

///---------------------------------------------------
/// NO COMPARISONS

void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minidx = i;
        for (int j = i + 1; j < n; j++) if (a[j] < a[minidx]) minidx = j;
        swap(a[i], a[minidx]);
    }
}

void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) if (a[j] > a[j + 1]) swap(a[j], a[j + 1]);
    }
}

void insertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int x = a[i], j = i - 1;
        while (j >= 0 && a[j] > x) { a[j + 1] = a[j]; j--; }
        a[j + 1] = x;
    }
}

void binaryInsertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int x = a[i], left = 0, right = i - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (a[mid] > x) right = mid - 1; else left = mid + 1;
        }
        for (int j = i - 1; j >= left; j--) a[j + 1] = a[j];
        a[left] = x;
    }
}

void shakerSort(int a[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        for (int i = left; i < right; i++) if (a[i] > a[i + 1]) swap(a[i], a[i + 1]);
        right--;
        for (int i = right; i > left; i--) if (a[i] < a[i - 1]) swap(a[i], a[i - 1]);
        left++;
    }
}