#ifndef QUEUEDATA_H
#define QUEUEDATA_H

#include "rental.h"

const int QUEUE_MAX = 100;

class QueueArray {
public:
    QueueArray();

    bool enqueue(const Rental& data);
    bool dequeue(Rental& data);
    bool front(Rental& data) const;
    bool rear(Rental& data) const;
    bool isEmpty() const;
    bool isFull() const;
    int count() const;
    Rental valueAt(int logicalIndex) const;
    void clear();

private:
    Rental data[QUEUE_MAX];
    int frontIndex;
    int rearIndex;
    int jumlah;
};

struct NodeQueue {
    Rental data;
    NodeQueue* next;
};

class QueueLinked {
public:
    QueueLinked();
    ~QueueLinked();

    QueueLinked(const QueueLinked&) = delete;
    QueueLinked& operator=(const QueueLinked&) = delete;

    bool enqueue(const Rental& data);
    bool dequeue(Rental& data);
    bool front(Rental& data) const;
    bool rear(Rental& data) const;
    bool isEmpty() const;
    int count() const;
    NodeQueue* getFrontNode() const;
    void clear();

private:
    NodeQueue* frontNode;
    NodeQueue* rearNode;
    int jumlah;
};

#endif
