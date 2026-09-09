#ifndef SORTING_H
#define SORTING_H

#include "rental.h"

class Sorting {
public:
    static void bubbleSort(Rental* arr, int n, int field);
    static void selectionSort(Rental* arr, int n, int field);
    static void insertionSort(Rental* arr, int n, int field);

private:
    static bool lebihKecil(const Rental& a, const Rental& b, int field);
};

#endif
