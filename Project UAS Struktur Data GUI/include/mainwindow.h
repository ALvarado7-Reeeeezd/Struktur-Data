#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "singlylist.h"
#include "doublylist.h"
#include "stackdata.h"
#include "queuedata.h"

class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTableWidget;
class QTabWidget;
class QTextEdit;
class QWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void sInsertAwal();
    void sInsertAkhir();
    void sInsertPosisi();
    void sDeleteId();
    void sDisplay();
    void sClear();

    void dTambahTransaksi();
    void dDeleteId();
    void dDisplayMaju();
    void dDisplayMundur();
    void dClear();

    void stackArrayPush();
    void stackArrayPop();
    void stackArrayPeek();
    void stackArrayClear();
    void stackLinkedPush();
    void stackLinkedPop();
    void stackLinkedPeek();
    void stackLinkedClear();

    void queueArrayEnqueue();
    void queueArrayDequeue();
    void queueArrayFront();
    void queueArrayRear();
    void queueArrayClear();
    void queueLinkedEnqueue();
    void queueLinkedDequeue();
    void queueLinkedFront();
    void queueLinkedRear();
    void queueLinkedClear();

    void recursiveDisplayPelanggan();
    void recursiveTotalPendapatan();

    void loadSortingData();
    void sortData();

    void searchSequentialArray();
    void searchSequentialLinked();
    void searchBinaryArray();

    void savePelanggan();
    void loadPelanggan();
    void saveTransaksi();
    void loadTransaksi();
    void browseFilePath();

    void resetAllInputs();
    void tampilkanTentang();

private:
    void setupMenu();
    void setupUI();
    void setupDashboardTab();
    void setupSinglyTab();
    void setupDoublyTab();
    void setupStackTab();
    void setupQueueTab();
    void setupRecursiveTab();
    void setupSortingTab();
    void setupSearchingTab();
    void setupFileTab();
    void setupOutputTab();

    QGroupBox* createRentalForm(QWidget* parent, QLineEdit*& id, QLineEdit*& nama,
                                QComboBox*& jenis, QLineEdit*& durasi,
                                QLineEdit*& posisi, bool withPosisi);
    QTableWidget* createRentalTable(QWidget* parent);
    QTableWidget* createSingleColumnTable(QWidget* parent, const QString& header);

    Rental readRental(QLineEdit* id, QLineEdit* nama, QComboBox* jenis, QLineEdit* durasi, bool* ok);
    void addRentalRow(QTableWidget* table, const Rental& data);
    void fillTableFromArray(QTableWidget* table, const Rental* arr, int n);
    void refreshSinglyTable();
    void refreshDoublyForwardTable();
    void refreshDoublyBackwardTable();
    void refreshStackTables();
    void refreshQueueTables();
    void logMessage(const QString& message);

    bool confirmClear(const QString& message);
    void pushAction(const QString& action);

private:
    SinglyList dataPelanggan;
    DoublyList dataTransaksi;
    StackArray stackArr;
    StackLinked stackLink;
    QueueArray queueArr;
    QueueLinked queueLink;

    QTabWidget* tabWidget;
    QTextEdit* outputLog;

    QLineEdit* sId;
    QLineEdit* sNama;
    QComboBox* sJenis;
    QLineEdit* sDurasi;
    QLineEdit* sPosisi;
    QTableWidget* sTable;

    QLineEdit* dId;
    QLineEdit* dNama;
    QComboBox* dJenis;
    QLineEdit* dDurasi;
    QLineEdit* dNoPosisi;
    QTableWidget* dTable;

    QLineEdit* stackInput;
    QTableWidget* stackArrayTable;
    QTableWidget* stackLinkedTable;

    QLineEdit* qId;
    QLineEdit* qNama;
    QComboBox* qJenis;
    QLineEdit* qDurasi;
    QLineEdit* qNoPosisi;
    QTableWidget* queueArrayTable;
    QTableWidget* queueLinkedTable;

    QTextEdit* recursiveOutput;

    QComboBox* sortAlgo;
    QComboBox* sortField;
    QTableWidget* sortBeforeTable;
    QTableWidget* sortAfterTable;
    Rental sortingCache[QUEUE_MAX];
    int sortingCount;

    QLineEdit* searchIdInput;
    QTextEdit* searchOutput;

    QLineEdit* filePathInput;
};

#endif
