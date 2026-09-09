#include "doublylist.h"

DoublyList::DoublyList()
    : head(nullptr), tail(nullptr), jumlah(0) {}

DoublyList::~DoublyList() {
    clear();
}

NodeDoubly* DoublyList::getHead() const {
    return head;
}

NodeDoubly* DoublyList::getTail() const {
    return tail;
}

bool DoublyList::isEmpty() const {
    return head == nullptr;
}

int DoublyList::count() const {
    return jumlah;
}

bool DoublyList::containsId(int id) const {
    Rental temp;
    return findById(id, temp);
}

bool DoublyList::findById(int id, Rental& result) const {
    NodeDoubly* current = head;

    while (current != nullptr) {
        if (current->data.id == id) {
            result = current->data;
            return true;
        }
        current = current->next;
    }

    return false;
}

void DoublyList::insertAkhir(const Rental& data) {
    NodeDoubly* newNode = new NodeDoubly;
    newNode->data = data;
    newNode->prev = nullptr;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        jumlah++;
        return;
    }

    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
    jumlah++;
}

bool DoublyList::deleteById(int id) {
    NodeDoubly* current = head;

    while (current != nullptr && current->data.id != id) {
        current = current->next;
    }

    if (current == nullptr) {
        return false;
    }

    if (current == head) {
        head = current->next;
    }

    if (current == tail) {
        tail = current->prev;
    }

    if (current->prev != nullptr) {
        current->prev->next = current->next;
    }

    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }

    delete current;
    jumlah--;

    return true;
}

void DoublyList::clear() {
    NodeDoubly* current = head;

    while (current != nullptr) {
        NodeDoubly* temp = current;
        current = current->next;
        delete temp;
    }

    head = nullptr;
    tail = nullptr;
    jumlah = 0;
}

int DoublyList::toArray(Rental* arr, int maxSize) const {
    int index = 0;
    NodeDoubly* current = head;

    while (current != nullptr && index < maxSize) {
        arr[index] = current->data;
        current = current->next;
        index++;
    }

    return index;
}
