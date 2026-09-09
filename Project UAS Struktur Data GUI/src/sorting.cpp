#include "sorting.h"

bool Sorting::lebihKecil(const Rental& a, const Rental& b, int field) {
    if (field == 0) {
        return a.id < b.id;
    }

    if (field == 1) {
        return QString::compare(a.nama, b.nama, Qt::CaseInsensitive) < 0;
    }

    return a.totalBayar < b.totalBayar;
}

void Sorting::bubbleSort(Rental* arr, int n, int field) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (!lebihKecil(arr[j], arr[j + 1], field)) {
                Rental temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void Sorting::selectionSort(Rental* arr, int n, int field) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (lebihKecil(arr[j], arr[minIndex], field)) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            Rental temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

void Sorting::insertionSort(Rental* arr, int n, int field) {
    for (int i = 1; i < n; i++) {
        Rental key = arr[i];
        int j = i - 1;

        while (j >= 0 && lebihKecil(key, arr[j], field)) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}
