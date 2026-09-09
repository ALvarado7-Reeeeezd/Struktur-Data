#include "stackdata.h"

StackArray::StackArray()
    : topIndex(-1) {}

bool StackArray::push(const QString& aksi) {
    if (isFull()) {
        return false;
    }

    topIndex++;
    data[topIndex] = aksi;
    return true;
}

bool StackArray::pop(QString& aksi) {
    if (isEmpty()) {
        return false;
    }

    aksi = data[topIndex];
    topIndex--;
    return true;
}

bool StackArray::peek(QString& aksi) const {
    if (isEmpty()) {
        return false;
    }

    aksi = data[topIndex];
    return true;
}

bool StackArray::isEmpty() const {
    return topIndex == -1;
}

bool StackArray::isFull() const {
    return topIndex == STACK_MAX - 1;
}

int StackArray::count() const {
    return topIndex + 1;
}

QString StackArray::valueFromTop(int indexFromTop) const {
    int actualIndex = topIndex - indexFromTop;

    if (actualIndex < 0 || actualIndex > topIndex) {
        return "";
    }

    return data[actualIndex];
}

void StackArray::clear() {
    topIndex = -1;
}

StackLinked::StackLinked()
    : topNode(nullptr), jumlah(0) {}

StackLinked::~StackLinked() {
    clear();
}

bool StackLinked::push(const QString& aksi) {
    NodeStack* newNode = new NodeStack;
    newNode->aksi = aksi;
    newNode->next = topNode;
    topNode = newNode;
    jumlah++;
    return true;
}

bool StackLinked::pop(QString& aksi) {
    if (isEmpty()) {
        return false;
    }

    NodeStack* temp = topNode;
    aksi = temp->aksi;
    topNode = topNode->next;
    delete temp;
    jumlah--;
    return true;
}

bool StackLinked::peek(QString& aksi) const {
    if (isEmpty()) {
        return false;
    }

    aksi = topNode->aksi;
    return true;
}

bool StackLinked::isEmpty() const {
    return topNode == nullptr;
}

int StackLinked::count() const {
    return jumlah;
}

NodeStack* StackLinked::getTop() const {
    return topNode;
}

void StackLinked::clear() {
    NodeStack* current = topNode;

    while (current != nullptr) {
        NodeStack* temp = current;
        current = current->next;
        delete temp;
    }

    topNode = nullptr;
    jumlah = 0;
}
