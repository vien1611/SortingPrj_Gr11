#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

struct Record {
    long long comparison;
    double time;
};

Record getRecord(int a[], int n,
    void (*sortFunctionCmp)(int[], int, long long&),
    void (*sortFunction)(int[], int));


///NO COMPARISONS

// Quadratic
void selectionSort(int a[], int n);
void insertionSort(int a[], int n);
void binaryInsertionSort(int a[], int n);
void bubbleSort(int a[], int n);
void shakerSort(int a[], int n);

// Efficient
void shellSort(int a[], int n);
void heapSort(int a[], int n);
void mergeSort(int a[], int n);
void quickSort(int a[], int n);

// Linear
void countingSort(int a[], int n);
void radixSort(int a[], int n);
void flashSort(int a[], int n);


//COMPARISONS

void selectionSort(int a[], int n, long long &comparison);
void insertionSort(int a[], int n, long long &comparison);
void binaryInsertionSort(int a[], int n, long long &comparison);
void bubbleSort(int a[], int n, long long &comparison);
void shakerSort(int a[], int n, long long &comparison);

void shellSort(int a[], int n, long long &comparison);
void heapSort(int a[], int n, long long &comparison);
void mergeSort(int a[], int n, long long &comparison);
void quickSort(int a[], int n, long long &comparison);

void countingSort(int a[], int n, long long &comparison);
void radixSort(int a[], int n, long long &comparison);
void flashSort(int a[], int n, long long &comparison);


//DATA

void GenerateRandomData(int a[], int n);
void GenerateSortedData(int a[], int n);
void GenerateReverseData(int a[], int n);
void GenerateNearlySortedData(int a[], int n);

void GenerateData(int a[], int n, int dataType);


//CMD

void processArg(int argc, char* argv[]);