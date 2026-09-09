#ifndef DOUBLYLIST_H
#define DOUBLYLIST_H

#include "rental.h"

struct NodeDoubly {
    Rental data;
    NodeDoubly* prev;
    NodeDoubly* next;
};

class DoublyList {
public:
    DoublyList();
    ~DoublyList();

    DoublyList(const DoublyList&) = delete;
    DoublyList& operator=(const DoublyList&) = delete;

    NodeDoubly* getHead() const;
    NodeDoubly* getTail() const;
    bool isEmpty() const;
    int count() const;

    bool containsId(int id) const;
    bool findById(int id, Rental& result) const;

    void insertAkhir(const Rental& data);
    bool deleteById(int id);
    void clear();

    int toArray(Rental* arr, int maxSize) const;

private:
    NodeDoubly* head;
    NodeDoubly* tail;
    int jumlah;
};

#endif
