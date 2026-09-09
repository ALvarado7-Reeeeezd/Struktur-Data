#include "recursive.h"

QString Recursive::displaySingly(NodeSingly* node) {
    if (node == nullptr) {
        return "";
    }

    return rentalToText(node->data) + "\n" + displaySingly(node->next);
}

int Recursive::totalPendapatan(NodeDoubly* node) {
    if (node == nullptr) {
        return 0;
    }

    return node->data.totalBayar + totalPendapatan(node->next);
}
