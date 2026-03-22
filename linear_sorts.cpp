#include "sorting.h"

///COMPARISONS

void countingSort(int a[], int n, long long &comparisons) {
    comparisons = 0;
    if (++comparisons && n <= 0) return;
    int maxVal = a[0], minVal = a[0];
    for (int i = 1; ++comparisons && i < n; i++) {
        if (++comparisons && a[i] > maxVal) maxVal = a[i];
        if (++comparisons && a[i] < minVal) minVal = a[i];
    }
    int range = maxVal - minVal + 1;
    int* count = new int[range]();
    int* output = new int[n];
    for (int i = 0; ++comparisons && i < n; i++) count[a[i] - minVal]++;
    for (int i = 1; ++comparisons && i < range; i++) count[i] += count[i - 1];
    for (int i = n - 1; ++comparisons && i >= 0; i--) {
        output[count[a[i] - minVal] - 1] = a[i];
        count[a[i] - minVal]--;
    }
    for (int i = 0; ++comparisons && i < n; i++) a[i] = output[i];
    delete[] count; delete[] output;
}

void countingSubForRadix(int a[], int n, int exp, long long &comparisons) {
    int* output = new int[n];
    int count[10] = {0};

    for (int i = 0; ++comparisons && i < n; i++) 
        count[(a[i] / exp) % 10]++;

    for (int i = 1; ++comparisons && i < 10; i++) 
        count[i] += count[i - 1];

    for (int i = n - 1; ++comparisons && i >= 0; i--) {
        output[count[(a[i] / exp) % 10] - 1] = a[i];
        count[(a[i] / exp) % 10]--;
    }

    for (int i = 0; ++comparisons && i < n; i++) 
        a[i] = output[i];

    delete[] output;
}

void radixSort(int a[], int n, long long &comparisons) {
    comparisons = 0;
    if (++comparisons && n <= 0) return;
    int maxVal = a[0];
    for (int i = 1; ++comparisons && i < n; i++) {
        comparisons++; // Đếm a[i] > maxVal
        if (a[i] > maxVal) maxVal = a[i];
    }
    for (int exp = 1; ++comparisons && maxVal / exp > 0; exp *= 10) {
        countingSubForRadix(a, n, exp, comparisons); 
    }
}

int getK(int x, int m, int max, int min) {
    return (int)((m - 1) * (double)(x - min) / (max - min));
}

void flashSort(int a[], int n, long long& comparisons) {
    comparisons = 0;
    if (++comparisons && n <= 1) return;
    int m = (int)(n * 0.45);
    if (++comparisons && m <= 2) m = 2;
    int* bucket = new int[m]();
    int max = a[0], min = a[0];
    for (int i = 1; ++comparisons && i < n; ++i) {
        if (++comparisons && a[i] > max) max = a[i];
        else if (++comparisons && a[i] < min) min = a[i];
    }
    if (++comparisons && max == min) { delete[] bucket; return; }
    for (int i = 0; ++comparisons && i < n; ++i) bucket[getK(a[i], m, max, min)]++;
    for (int i = 1; ++comparisons && i < m; ++i) bucket[i] += bucket[i - 1];

    int count = 0, i = 0;
    while (++comparisons && count < n) {
        while (++comparisons && i >= bucket[getK(a[i], m, max, min)]) i++;
        int z = a[i];
        while (++comparisons && i != bucket[getK(z, m, max, min)]) {
            int k = getK(z, m, max, min);
            int y = a[bucket[k] - 1];
            a[--bucket[k]] = z;
            z = y;
            count++;
        }
    }
    for (int k = 1; ++comparisons && k < m; k++) {
        for (int i = bucket[k] - 2; ++comparisons && i >= bucket[k - 1]; i--) {
            if (++comparisons && a[i] > a[i + 1]) {
                int t = a[i], j = i;
                while (++comparisons && t > a[j + 1]) {
                    a[j] = a[j + 1];
                    j++;
                    if (++comparisons && j >= n - 1) break;
                }
                a[j] = t;
            }
        }
    }
    delete[] bucket;
}

///--------------------------------------
/// NO COMPARISONS

void countingSort(int a[], int n) {
    if (n <= 1) return;
    int maxVal = a[0], minVal = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > maxVal) maxVal = a[i];
        if (a[i] < minVal) minVal = a[i];
    }
    int range = maxVal - minVal + 1;
    int* count = new int[range]();
    int* output = new int[n];
    for (int i = 0; i < n; i++) count[a[i] - minVal]++;
    for (int i = 1; i < range; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[a[i] - minVal] - 1] = a[i];
        count[a[i] - minVal]--;
    }
    for (int i = 0; i < n; i++) a[i] = output[i];
    delete[] count; delete[] output;
}

void countingSubForRadix(int a[], int n, int exp) {
    int* output = new int[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++) count[(a[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(a[i] / exp) % 10] - 1] = a[i];
        count[(a[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) a[i] = output[i];

    delete[] output;
}

void radixSort(int a[], int n) {
    if (n <= 1) return;
    int maxVal = a[0];
    for (int i = 1; i < n; i++) if (a[i] > maxVal) maxVal = a[i];
    for (int exp = 1; maxVal / exp > 0; exp *= 10) countingSubForRadix(a, n, exp);
}

void flashSort(int a[], int n) {
    if (n <= 1) return;
    int m = (int)(n * 0.45);
    if (m <= 2) m = 2;
    int* bucket = new int[m]();
    int max = a[0], min = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > max) max = a[i];
        else if (a[i] < min) min = a[i];
    }
    if (max == min) { delete[] bucket; return; }
    for (int i = 0; i < n; ++i) bucket[getK(a[i], m, max, min)]++;
    for (int i = 1; i < m; ++i) bucket[i] += bucket[i - 1];
    int count = 0, i = 0;
    while (count < n) {
        while (i >= bucket[getK(a[i], m, max, min)]) i++;
        int z = a[i];
        while (i != bucket[getK(z, m, max, min)]) {
            int k = getK(z, m, max, min);
            int y = a[bucket[k] - 1];
            a[--bucket[k]] = z;
            z = y;
            count++;
        }
    }
    for (int k = 1; k < m; k++) {
        for (int i = bucket[k] - 2; i >= bucket[k - 1]; i--) {
            if (a[i] > a[i + 1]) {
                int t = a[i], j = i;
                while (t > a[j + 1]) {
                    a[j] = a[j + 1];
                    j++;
                    if (j >= n - 1) break;
                }
                a[j] = t;
            }
        }
    }
    delete[] bucket;
}