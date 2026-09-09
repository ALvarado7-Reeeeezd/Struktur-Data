#include "filehandler.h"

#include <QFile>
#include <QTextStream>

bool FileHandler::saveSingly(const QString& filePath, const SinglyList& list, QString& message) {
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        message = "Gagal membuka file untuk save.";
        return false;
    }

    QTextStream out(&file);
    NodeSingly* current = list.getHead();

    while (current != nullptr) {
        out << rentalToFileLine(current->data) << "\n";
        current = current->next;
    }

    message = "Data pelanggan berhasil disimpan.";
    return true;
}

bool FileHandler::loadSingly(const QString& filePath, SinglyList& list, QString& message) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        message = "Gagal membuka file untuk load.";
        return false;
    }

    list.clear();
    QTextStream in(&file);
    int jumlahLoad = 0;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (line.isEmpty()) {
            continue;
        }

        Rental data;
        if (fileLineToRental(line, data)) {
            list.insertAkhir(data);
            jumlahLoad++;
        }
    }

    message = QString("Data pelanggan berhasil diload: %1 data.").arg(jumlahLoad);
    return true;
}

bool FileHandler::saveDoubly(const QString& filePath, const DoublyList& list, QString& message) {
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        message = "Gagal membuka file untuk save transaksi.";
        return false;
    }

    QTextStream out(&file);
    NodeDoubly* current = list.getHead();

    while (current != nullptr) {
        out << rentalToFileLine(current->data) << "\n";
        current = current->next;
    }

    message = "Data transaksi berhasil disimpan.";
    return true;
}

bool FileHandler::loadDoubly(const QString& filePath, DoublyList& list, QString& message) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        message = "Gagal membuka file transaksi untuk load.";
        return false;
    }

    list.clear();
    QTextStream in(&file);
    int jumlahLoad = 0;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (line.isEmpty()) {
            continue;
        }

        Rental data;
        if (fileLineToRental(line, data)) {
            list.insertAkhir(data);
            jumlahLoad++;
        }
    }

    message = QString("Data transaksi berhasil diload: %1 data.").arg(jumlahLoad);
    return true;
}
