#include "singlylist.h"

SinglyList::SinglyList()
    : head(nullptr), jumlah(0) {}

SinglyList::~SinglyList() {
    clear();
}

NodeSingly* SinglyList::getHead() const {
    return head;
}

bool SinglyList::isEmpty() const {
    return head == nullptr;
}

int SinglyList::count() const {
    return jumlah;
}

bool SinglyList::containsId(int id) const {
    Rental temp;
    return findById(id, temp);
}

bool SinglyList::findById(int id, Rental& result) const {
    NodeSingly* current = head;

    while (current != nullptr) {
        if (current->data.id == id) {
            result = current->data;
            return true;
        }
        current = current->next;
    }

    return false;
}

void SinglyList::insertAwal(const Rental& data) {
    NodeSingly* newNode = new NodeSingly;
    newNode->data = data;
    newNode->next = head;
    head = newNode;
    jumlah++;
}

void SinglyList::insertAkhir(const Rental& data) {
    NodeSingly* newNode = new NodeSingly;
    newNode->data = data;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        jumlah++;
        return;
    }

    NodeSingly* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = newNode;
    jumlah++;
}

bool SinglyList::insertPosisi(const Rental& data, int posisi) {
    if (posisi <= 0) {
        return false;
    }

    if (posisi == 1) {
        insertAwal(data);
        return true;
    }

    NodeSingly* current = head;
    int index = 1;

    while (current != nullptr && index < posisi - 1) {
        current = current->next;
        index++;
    }

    if (current == nullptr) {
        return false;
    }

    NodeSingly* newNode = new NodeSingly;
    newNode->data = data;
    newNode->next = current->next;
    current->next = newNode;
    jumlah++;

    return true;
}

bool SinglyList::deleteById(int id) {
    if (head == nullptr) {
        return false;
    }

    if (head->data.id == id) {
        NodeSingly* temp = head;
        head = head->next;
        delete temp;
        jumlah--;
        return true;
    }

    NodeSingly* current = head;
    while (current->next != nullptr && current->next->data.id != id) {
        current = current->next;
    }

    if (current->next == nullptr) {
        return false;
    }

    NodeSingly* temp = current->next;
    current->next = temp->next;
    delete temp;
    jumlah--;

    return true;
}

void SinglyList::clear() {
    NodeSingly* current = head;

    while (current != nullptr) {
        NodeSingly* temp = current;
        current = current->next;
        delete temp;
    }

    head = nullptr;
    jumlah = 0;
}

int SinglyList::toArray(Rental* arr, int maxSize) const {
    int index = 0;
    NodeSingly* current = head;

    while (current != nullptr && index < maxSize) {
        arr[index] = current->data;
        current = current->next;
        index++;
    }

    return index;
}
