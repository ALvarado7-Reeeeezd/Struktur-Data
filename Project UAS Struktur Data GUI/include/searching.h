#ifndef SEARCHING_H
#define SEARCHING_H

#include "rental.h"
#include "singlylist.h"

class Searching {
public:
    static int sequentialArrayById(const Rental* arr, int n, int id);
    static int binaryArrayById(const Rental* arr, int n, int id);
    static bool sequentialLinkedListById(NodeSingly* head, int id, Rental& result);
};

#endif
