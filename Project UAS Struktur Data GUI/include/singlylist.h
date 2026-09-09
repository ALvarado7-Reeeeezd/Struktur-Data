#ifndef SINGLYLIST_H
#define SINGLYLIST_H

#include "rental.h"

struct NodeSingly {
    Rental data;
    NodeSingly* next;
};

class SinglyList {
public:
    SinglyList();
    ~SinglyList();

    SinglyList(const SinglyList&) = delete;
    SinglyList& operator=(const SinglyList&) = delete;

    NodeSingly* getHead() const;
    bool isEmpty() const;
    int count() const;

    bool containsId(int id) const;
    bool findById(int id, Rental& result) const;

    void insertAwal(const Rental& data);
    void insertAkhir(const Rental& data);
    bool insertPosisi(const Rental& data, int posisi);
    bool deleteById(int id);
    void clear();

    int toArray(Rental* arr, int maxSize) const;

private:
    NodeSingly* head;
    int jumlah;
};

#endif
