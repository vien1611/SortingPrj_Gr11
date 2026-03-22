#include "sorting.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>
#include <chrono>
#include <cstring>

using namespace std;

struct SortAlgorithm {
    void (*noCmp)(int[], int);
    void (*withCmp)(int[], int, long long&);
};

map<string, SortAlgorithm> algos;

void initAlgos() {
    algos["selection-sort"] = {selectionSort, selectionSort};
    algos["insertion-sort"] = {insertionSort, insertionSort};
    algos["bubble-sort"] = {bubbleSort, bubbleSort};
    algos["shaker-sort"] = {shakerSort, shakerSort};
    algos["shell-sort"] = {shellSort, shellSort};
    algos["heap-sort"] = {heapSort, heapSort};
    algos["merge-sort"] = {mergeSort, mergeSort};
    algos["quick-sort"] = {quickSort, quickSort};
    algos["counting-sort"] = {countingSort, countingSort};
    algos["radix-sort"] = {radixSort, radixSort};
    algos["flash-sort"] = {flashSort, flashSort};
    algos["binary-insertion-sort"] = {binaryInsertionSort, binaryInsertionSort};
}

void writeArrayToFile(string fileName, int a[], int n) {
    ofstream f(fileName);
    f << n << endl;
    for (int i = 0; i < n; i++) f << a[i] << (i == n - 1 ? "" : " ");
    f.close();
}

int* loadArrayFromFile(string fileName, int& n) {
    ifstream f(fileName);
    if (!f.is_open()) return nullptr;
    f >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++) f >> a[i];
    f.close();
    return a;
}

Record runSort(int a[], int n, string algoName, bool measureTime, bool measureCmp) {
    Record res = {0, 0.0};
    SortAlgorithm sa = algos[algoName];

    if (measureCmp) {
        int* temp = new int[n];
        memcpy(temp, a, n * sizeof(int));
        sa.withCmp(temp, n, res.comparison);
        delete[] temp;
    }

    if (measureTime) {
        int* temp = new int[n];
        memcpy(temp, a, n * sizeof(int));
        auto start = chrono::high_resolution_clock::now();
        sa.noCmp(temp, n);
        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> diff = stop - start;
        res.time = diff.count();
        writeArrayToFile("output.txt", temp, n);
        delete[] temp;
    }
    return res;
}

void printSingleResult(Record res, string outputParam) {
    if (outputParam == "-time" || outputParam == "-both")
        cout << "Running time: " << fixed << setprecision(3) << res.time << " ms" << endl;
    if (outputParam == "-comp" || outputParam == "-both")
        cout << "Comparisons: " << res.comparison << endl;
}

int main(int argc, char* argv[]) {
    initAlgos();
    if (argc < 4) return 0;

    string mode = argv[1];
    if (mode == "-a") {
        string algo = argv[2];
        cout << "ALGORITHM MODE\nAlgorithm: " << algo << endl;
        
        // Command 1: File có sẵn
        if (argc == 5 && string(argv[3]).find(".txt") != string::npos) {
            int n; int* a = loadArrayFromFile(argv[3], n);
            cout << "Input file: " << argv[3] << "\nInput size: " << n << "\n-------------------------" << endl;
            Record res = runSort(a, n, algo, true, true);
            printSingleResult(res, argv[4]);
            delete[] a;
        } 
        // Command 3: ALL data arrangements
        else if (argc == 5) {
            int n = stoi(argv[3]);
            int dataTypes[] = {0, 3, 1, 2};
            string orders[] = {"Randomize", "Nearly Sorted", "Sorted", "Reversed"};
            string files[] = {"input_1.txt", "input_2.txt", "input_3.txt", "input_4.txt"};
            for (int i = 0; i < 4; i++) {
                int* a = new int[n];
                GenerateData(a, n, dataTypes[i]);
                writeArrayToFile(files[i], a, n);
                cout << "\nInput order: " << orders[i] << "\n-------------------------" << endl;
                Record res = runSort(a, n, algo, true, true);
                printSingleResult(res, argv[4]);
                delete[] a;
            }
        } 
        // Command 2: Tự tạo dữ liệu
        else if (argc == 6) {
            int n = stoi(argv[3]); string orderStr = argv[4];
            int orderType = (orderStr == "-rand") ? 0 : (orderStr == "-sorted") ? 1 : (orderStr == "-rev") ? 2 : (orderStr == "-nsorted") ? 3 : -1 ;
            /// Check loi commandline
            if (orderType == -1) {
                cout << "Loi: Tham so sap xep khong hop le!" << endl;
                return 1; 
            }
            int* a = new int[n]; GenerateData(a, n, orderType);
            writeArrayToFile("input.txt", a, n);
            cout << "Input size: " << n << "\nInput order: " << orderStr << "\n-------------------------" << endl;
            Record res = runSort(a, n, algo, true, true);
            printSingleResult(res, argv[5]);
            delete[] a;
        }
    } else if (mode == "-c") {
        string algo1 = argv[2], algo2 = argv[3];
        cout << "COMPARE MODE\nAlgorithm: " << algo1 << " | " << algo2 << endl;
        // Command 4: 2 algo trên file có sẵn
        if (argc == 5) {
            int n; int* a = loadArrayFromFile(argv[4], n);
            cout << "Input file: " << argv[4] << "\nInput size: " << n << "\n-------------------------" << endl;
            Record r1 = runSort(a, n, algo1, true, true);
            Record r2 = runSort(a, n, algo2, true, true);
            cout << "Running time: " << r1.time << " | " << r2.time << " ms\nComparisons: " << r1.comparison << " | " << r2.comparison << endl;
            delete[] a;
        } 
        // Command 5: 2 algo trên dữ liệu tự tạo
        else if (argc == 6) {
            int n = stoi(argv[4]); string orderStr = argv[5];
            int orderType = (orderStr == "-rand") ? 0 : (orderStr == "-sorted") ? 1 : (orderStr == "-rev") ? 2 : (orderStr == "-nsorted") ? 3 : -1 ;
            if (orderType == -1) {
                cout << "Loi: Tham so sap xep khong hop le!" << endl;
                return 1; 
            }
            int* a = new int[n]; GenerateData(a, n, orderType);
            writeArrayToFile("input.txt", a, n);
            cout << "Input size: " << n << "\nInput order: " << orderStr << "\n-------------------------" << endl;
            Record r1 = runSort(a, n, algo1, true, true);
            Record r2 = runSort(a, n, algo2, true, true);
            cout << "Running time: " << r1.time << " | " << r2.time << " ms\nComparisons: " << r1.comparison << " | " << r2.comparison << endl;
            delete[] a;
        }
    }
    return 0;
}