#ifndef STACKDATA_H
#define STACKDATA_H

#include <QString>

const int STACK_MAX = 100;

class StackArray {
public:
    StackArray();

    bool push(const QString& aksi);
    bool pop(QString& aksi);
    bool peek(QString& aksi) const;
    bool isEmpty() const;
    bool isFull() const;
    int count() const;
    QString valueFromTop(int indexFromTop) const;
    void clear();

private:
    QString data[STACK_MAX];
    int topIndex;
};

struct NodeStack {
    QString aksi;
    NodeStack* next;
};

class StackLinked {
public:
    StackLinked();
    ~StackLinked();

    StackLinked(const StackLinked&) = delete;
    StackLinked& operator=(const StackLinked&) = delete;

    bool push(const QString& aksi);
    bool pop(QString& aksi);
    bool peek(QString& aksi) const;
    bool isEmpty() const;
    int count() const;
    NodeStack* getTop() const;
    void clear();

private:
    NodeStack* topNode;
    int jumlah;
};

#endif
