#include "searching.h"

int Searching::sequentialArrayById(const Rental* arr, int n, int id) {
    for (int i = 0; i < n; i++) {
        if (arr[i].id == id) {
            return i;
        }
    }

    return -1;
}

int Searching::binaryArrayById(const Rental* arr, int n, int id) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid].id == id) {
            return mid;
        }

        if (arr[mid].id < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

bool Searching::sequentialLinkedListById(NodeSingly* head, int id, Rental& result) {
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
