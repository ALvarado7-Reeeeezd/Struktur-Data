#ifndef RENTAL_H
#define RENTAL_H

#include <QString>
#include <QStringList>

struct Rental {
    int id;
    QString nama;
    QString jenisPS;
    int durasiJam;
    int totalBayar;

    Rental()
        : id(0), nama(""), jenisPS("PS3"), durasiJam(0), totalBayar(0) {}

    Rental(int idValue, const QString& namaValue, const QString& jenisValue, int durasiValue)
        : id(idValue), nama(namaValue), jenisPS(jenisValue), durasiJam(durasiValue), totalBayar(0) {}
};

inline int tarifPerJam(const QString& jenisPS) {
    if (jenisPS == "PS3") {
        return 5000;
    }
    if (jenisPS == "PS4") {
        return 8000;
    }
    if (jenisPS == "PS5") {
        return 10000;
    }
    return 0;
}

inline int hitungBiaya(const QString& jenisPS, int durasiJam) {
    return tarifPerJam(jenisPS) * durasiJam;
}

inline QString rentalToText(const Rental& data) {
    return QString("ID: %1 | Nama: %2 | Jenis PS: %3 | Durasi: %4 jam | Total: Rp%5")
        .arg(data.id)
        .arg(data.nama)
        .arg(data.jenisPS)
        .arg(data.durasiJam)
        .arg(data.totalBayar);
}

inline QString rentalToFileLine(const Rental& data) {
    QString namaAman = data.nama;
    namaAman.replace(";", " ");

    return QString("%1;%2;%3;%4;%5")
        .arg(data.id)
        .arg(namaAman)
        .arg(data.jenisPS)
        .arg(data.durasiJam)
        .arg(data.totalBayar);
}

inline bool fileLineToRental(const QString& line, Rental& data) {
    QStringList parts = line.split(';');

    if (parts.size() != 5) {
        return false;
    }

    bool idOk = false;
    bool durasiOk = false;
    bool totalOk = false;

    int id = parts[0].toInt(&idOk);
    int durasi = parts[3].toInt(&durasiOk);
    int total = parts[4].toInt(&totalOk);

    if (!idOk || !durasiOk || !totalOk) {
        return false;
    }

    data.id = id;
    data.nama = parts[1].trimmed();
    data.jenisPS = parts[2].trimmed();
    data.durasiJam = durasi;
    data.totalBayar = total;

    return true;
}

#endif
