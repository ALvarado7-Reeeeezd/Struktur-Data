#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QString>
#include "singlylist.h"
#include "doublylist.h"

class FileHandler {
public:
    static bool saveSingly(const QString& filePath, const SinglyList& list, QString& message);
    static bool loadSingly(const QString& filePath, SinglyList& list, QString& message);
    static bool saveDoubly(const QString& filePath, const DoublyList& list, QString& message);
    static bool loadDoubly(const QString& filePath, DoublyList& list, QString& message);
};

#endif
