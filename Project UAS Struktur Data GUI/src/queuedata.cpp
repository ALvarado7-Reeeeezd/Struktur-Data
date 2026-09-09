#include "queuedata.h"

QueueArray::QueueArray()
    : frontIndex(0), rearIndex(-1), jumlah(0) {}

bool QueueArray::enqueue(const Rental& dataValue) {
    if (isFull()) {
        return false;
    }

    rearIndex = (rearIndex + 1) % QUEUE_MAX;
    data[rearIndex] = dataValue;
    jumlah++;
    return true;
}

bool QueueArray::dequeue(Rental& dataValue) {
    if (isEmpty()) {
        return false;
    }

    dataValue = data[frontIndex];
    frontIndex = (frontIndex + 1) % QUEUE_MAX;
    jumlah--;

    if (jumlah == 0) {
        frontIndex = 0;
        rearIndex = -1;
    }

    return true;
}

bool QueueArray::front(Rental& dataValue) const {
    if (isEmpty()) {
        return false;
    }

    dataValue = data[frontIndex];
    return true;
}

bool QueueArray::rear(Rental& dataValue) const {
    if (isEmpty()) {
        return false;
    }

    dataValue = data[rearIndex];
    return true;
}

bool QueueArray::isEmpty() const {
    return jumlah == 0;
}

bool QueueArray::isFull() const {
    return jumlah == QUEUE_MAX;
}

int QueueArray::count() const {
    return jumlah;
}

Rental QueueArray::valueAt(int logicalIndex) const {
    if (logicalIndex < 0 || logicalIndex >= jumlah) {
        return Rental{};
    }

    int actualIndex = (frontIndex + logicalIndex) % QUEUE_MAX;
    return data[actualIndex];
}

void QueueArray::clear() {
    frontIndex = 0;
    rearIndex = -1;
    jumlah = 0;
}

QueueLinked::QueueLinked()
    : frontNode(nullptr), rearNode(nullptr), jumlah(0) {}

QueueLinked::~QueueLinked() {
    clear();
}

bool QueueLinked::enqueue(const Rental& dataValue) {
    NodeQueue* newNode = new NodeQueue;
    newNode->data = dataValue;
    newNode->next = nullptr;

    if (rearNode == nullptr) {
        frontNode = newNode;
        rearNode = newNode;
    } else {
        rearNode->next = newNode;
        rearNode = newNode;
    }

    jumlah++;
    return true;
}

bool QueueLinked::dequeue(Rental& dataValue) {
    if (isEmpty()) {
        return false;
    }

    NodeQueue* temp = frontNode;
    dataValue = temp->data;
    frontNode = frontNode->next;

    if (frontNode == nullptr) {
        rearNode = nullptr;
    }

    delete temp;
    jumlah--;
    return true;
}

bool QueueLinked::front(Rental& dataValue) const {
    if (isEmpty()) {
        return false;
    }

    dataValue = frontNode->data;
    return true;
}

bool QueueLinked::rear(Rental& dataValue) const {
    if (isEmpty()) {
        return false;
    }

    dataValue = rearNode->data;
    return true;
}

bool QueueLinked::isEmpty() const {
    return frontNode == nullptr;
}

int QueueLinked::count() const {
    return jumlah;
}

NodeQueue* QueueLinked::getFrontNode() const {
    return frontNode;
}

void QueueLinked::clear() {
    NodeQueue* current = frontNode;

    while (current != nullptr) {
        NodeQueue* temp = current;
        current = current->next;
        delete temp;
    }

    frontNode = nullptr;
    rearNode = nullptr;
    jumlah = 0;
}
