#include "mainwindow.h"

#include "filehandler.h"
#include "recursive.h"
#include "searching.h"
#include "sorting.h"

#include <QAbstractItemView>
#include <QAction>
#include <QComboBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QList>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTabWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      tabWidget(nullptr),
      outputLog(nullptr),
      sId(nullptr), sNama(nullptr), sJenis(nullptr), sDurasi(nullptr), sPosisi(nullptr), sTable(nullptr),
      dId(nullptr), dNama(nullptr), dJenis(nullptr), dDurasi(nullptr), dNoPosisi(nullptr), dTable(nullptr),
      stackInput(nullptr), stackArrayTable(nullptr), stackLinkedTable(nullptr),
      qId(nullptr), qNama(nullptr), qJenis(nullptr), qDurasi(nullptr), qNoPosisi(nullptr),
      queueArrayTable(nullptr), queueLinkedTable(nullptr), recursiveOutput(nullptr),
      sortAlgo(nullptr), sortField(nullptr), sortBeforeTable(nullptr), sortAfterTable(nullptr), sortingCount(0),
      searchIdInput(nullptr), searchOutput(nullptr), filePathInput(nullptr) {
    setupMenu();
    setupUI();
}

MainWindow::~MainWindow() {}

void MainWindow::setupMenu() {
    QMenu* menuFile = menuBar()->addMenu("File");

    QAction* actionSavePelanggan = new QAction("Save Pelanggan", this);
    QAction* actionLoadPelanggan = new QAction("Load Pelanggan", this);
    QAction* actionKeluar = new QAction("Keluar", this);

    menuFile->addAction(actionSavePelanggan);
    menuFile->addAction(actionLoadPelanggan);
    menuFile->addSeparator();
    menuFile->addAction(actionKeluar);

    connect(actionSavePelanggan, &QAction::triggered, this, &MainWindow::savePelanggan);
    connect(actionLoadPelanggan, &QAction::triggered, this, &MainWindow::loadPelanggan);
    connect(actionKeluar, &QAction::triggered, this, &QMainWindow::close);

    QMenu* menuBantuan = menuBar()->addMenu("Bantuan");
    QAction* actionTentang = new QAction("Tentang Program", this);
    menuBantuan->addAction(actionTentang);
    connect(actionTentang, &QAction::triggered, this, &MainWindow::tampilkanTentang);
}

void MainWindow::setupUI() {
    tabWidget = new QTabWidget(this);

    setupDashboardTab();
    setupSinglyTab();
    setupDoublyTab();
    setupStackTab();
    setupQueueTab();
    setupRecursiveTab();
    setupSortingTab();
    setupSearchingTab();
    setupFileTab();
    setupOutputTab();

    setCentralWidget(tabWidget);
}

void MainWindow::setupDashboardTab() {
    QWidget* dashboard = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(dashboard);

    QLabel* title = new QLabel("SISTEM RENTAL PS & ANTRIAN MAIN GAME", dashboard);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 24px; font-weight: bold; margin: 15px;");

    QLabel* desc = new QLabel(
        "Project UAS Struktur Data berbasis C++ dan Qt Widgets.\n\n"
        "Fitur sesuai rubrik:\n"
        "1. Singly Linked List - Data pelanggan\n"
        "2. Doubly Linked List - Riwayat transaksi\n"
        "3. Stack Array dan Stack Linked List - Riwayat aksi\n"
        "4. Queue Array Circular dan Queue Linked List - Antrian main\n"
        "5. Recursive - Display pelanggan dan total pendapatan\n"
        "6. Sorting - Bubble, Selection, Insertion\n"
        "7. Searching - Sequential dan Binary Search\n"
        "8. Save / Load File\n\n"
        "Catatan: struktur data dibuat manual memakai struct, pointer, new, dan delete.",
        dashboard
    );
    desc->setStyleSheet("font-size: 14px; margin: 20px;");
    desc->setAlignment(Qt::AlignTop);

    layout->addWidget(title);
    layout->addWidget(desc);
    layout->addStretch();

    tabWidget->addTab(dashboard, "Dashboard");
}

QGroupBox* MainWindow::createRentalForm(QWidget* parent, QLineEdit*& id, QLineEdit*& nama,
                                        QComboBox*& jenis, QLineEdit*& durasi,
                                        QLineEdit*& posisi, bool withPosisi) {
    QGroupBox* box = new QGroupBox("Input Data Rental", parent);
    QFormLayout* form = new QFormLayout(box);

    id = new QLineEdit(box);
    nama = new QLineEdit(box);
    jenis = new QComboBox(box);
    durasi = new QLineEdit(box);
    posisi = nullptr;

    jenis->addItem("PS3");
    jenis->addItem("PS4");
    jenis->addItem("PS5");

    id->setPlaceholderText("Contoh: 1");
    nama->setPlaceholderText("Contoh: Budi");
    durasi->setPlaceholderText("Contoh: 2");

    form->addRow("ID:", id);
    form->addRow("Nama:", nama);
    form->addRow("Jenis PS:", jenis);
    form->addRow("Durasi Jam:", durasi);

    if (withPosisi) {
        posisi = new QLineEdit(box);
        posisi->setPlaceholderText("Khusus insert posisi, contoh: 2");
        form->addRow("Posisi:", posisi);
    }

    return box;
}

QTableWidget* MainWindow::createRentalTable(QWidget* parent) {
    QTableWidget* table = new QTableWidget(parent);
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels(QStringList() << "ID" << "Nama" << "Jenis PS" << "Durasi" << "Total Bayar");
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    return table;
}

QTableWidget* MainWindow::createSingleColumnTable(QWidget* parent, const QString& header) {
    QTableWidget* table = new QTableWidget(parent);
    table->setColumnCount(1);
    table->setHorizontalHeaderLabels(QStringList() << header);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    return table;
}

void MainWindow::setupSinglyTab() {
    QWidget* tab = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(tab);

    mainLayout->addWidget(createRentalForm(tab, sId, sNama, sJenis, sDurasi, sPosisi, true));

    QGridLayout* buttons = new QGridLayout();
    QPushButton* btnInsertAwal = new QPushButton("Insert Awal", tab);
    QPushButton* btnInsertAkhir = new QPushButton("Insert Akhir", tab);
    QPushButton* btnInsertPosisi = new QPushButton("Insert Posisi", tab);
    QPushButton* btnDelete = new QPushButton("Delete ID", tab);
    QPushButton* btnDisplay = new QPushButton("Traversal / Display", tab);
    QPushButton* btnClear = new QPushButton("Hapus Semua", tab);
    QPushButton* btnReset = new QPushButton("Reset Input", tab);

    buttons->addWidget(btnInsertAwal, 0, 0);
    buttons->addWidget(btnInsertAkhir, 0, 1);
    buttons->addWidget(btnInsertPosisi, 0, 2);
    buttons->addWidget(btnDelete, 1, 0);
    buttons->addWidget(btnDisplay, 1, 1);
    buttons->addWidget(btnClear, 1, 2);
    buttons->addWidget(btnReset, 2, 0, 1, 3);

    sTable = createRentalTable(tab);

    mainLayout->addLayout(buttons);
    mainLayout->addWidget(sTable);

    connect(btnInsertAwal, &QPushButton::clicked, this, &MainWindow::sInsertAwal);
    connect(btnInsertAkhir, &QPushButton::clicked, this, &MainWindow::sInsertAkhir);
    connect(btnInsertPosisi, &QPushButton::clicked, this, &MainWindow::sInsertPosisi);
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::sDeleteId);
    connect(btnDisplay, &QPushButton::clicked, this, &MainWindow::sDisplay);
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::sClear);
    connect(btnReset, &QPushButton::clicked, this, &MainWindow::resetAllInputs);

    tabWidget->addTab(tab, "Singly List");
}

void MainWindow::setupDoublyTab() {
    QWidget* tab = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(tab);

    mainLayout->addWidget(createRentalForm(tab, dId, dNama, dJenis, dDurasi, dNoPosisi, false));

    QGridLayout* buttons = new QGridLayout();
    QPushButton* btnAdd = new QPushButton("Tambah Transaksi", tab);
    QPushButton* btnDelete = new QPushButton("Delete ID", tab);
    QPushButton* btnForward = new QPushButton("Display Maju", tab);
    QPushButton* btnBackward = new QPushButton("Display Mundur", tab);
    QPushButton* btnClear = new QPushButton("Hapus Semua", tab);
    QPushButton* btnReset = new QPushButton("Reset Input", tab);

    buttons->addWidget(btnAdd, 0, 0);
    buttons->addWidget(btnDelete, 0, 1);
    buttons->addWidget(btnForward, 0, 2);
    buttons->addWidget(btnBackward, 1, 0);
    buttons->addWidget(btnClear, 1, 1);
    buttons->addWidget(btnReset, 1, 2);

    dTable = createRentalTable(tab);

    mainLayout->addLayout(buttons);
    mainLayout->addWidget(dTable);

    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::dTambahTransaksi);
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::dDeleteId);
    connect(btnForward, &QPushButton::clicked, this, &MainWindow::dDisplayMaju);
    connect(btnBackward, &QPushButton::clicked, this, &MainWindow::dDisplayMundur);
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::dClear);
    connect(btnReset, &QPushButton::clicked, this, &MainWindow::resetAllInputs);

    tabWidget->addTab(tab, "Doubly List");
}

void MainWindow::setupStackTab() {
    QWidget* tab = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(tab);

    QGroupBox* inputBox = new QGroupBox("Input Aksi Stack", tab);
    QFormLayout* form = new QFormLayout(inputBox);
    stackInput = new QLineEdit(inputBox);
    stackInput->setPlaceholderText("Contoh: Tambah pelanggan Budi");
    form->addRow("Aksi:", stackInput);
    mainLayout->addWidget(inputBox);

    QGridLayout* buttons = new QGridLayout();
    QPushButton* btnArrayPush = new QPushButton("Array Push", tab);
    QPushButton* btnArrayPop = new QPushButton("Array Pop", tab);
    QPushButton* btnArrayPeek = new QPushButton("Array Peek", tab);
    QPushButton* btnArrayClear = new QPushButton("Array Clear", tab);
    QPushButton* btnLinkedPush = new QPushButton("Linked Push", tab);
    QPushButton* btnLinkedPop = new QPushButton("Linked Pop", tab);
    QPushButton* btnLinkedPeek = new QPushButton("Linked Peek", tab);
    QPushButton* btnLinkedClear = new QPushButton("Linked Clear", tab);

    buttons->addWidget(btnArrayPush, 0, 0);
    buttons->addWidget(btnArrayPop, 0, 1);
    buttons->addWidget(btnArrayPeek, 0, 2);
    buttons->addWidget(btnArrayClear, 0, 3);
    buttons->addWidget(btnLinkedPush, 1, 0);
    buttons->addWidget(btnLinkedPop, 1, 1);
    buttons->addWidget(btnLinkedPeek, 1, 2);
    buttons->addWidget(btnLinkedClear, 1, 3);

    QGridLayout* tables = new QGridLayout();
    stackArrayTable = createSingleColumnTable(tab, "Stack Array - Top ke Bottom");
    stackLinkedTable = createSingleColumnTable(tab, "Stack Linked List - Top ke Bottom");
    tables->addWidget(stackArrayTable, 0, 0);
    tables->addWidget(stackLinkedTable, 0, 1);

    mainLayout->addLayout(buttons);
    mainLayout->addLayout(tables);

    connect(btnArrayPush, &QPushButton::clicked, this, &MainWindow::stackArrayPush);
    connect(btnArrayPop, &QPushButton::clicked, this, &MainWindow::stackArrayPop);
    connect(btnArrayPeek, &QPushButton::clicked, this, &MainWindow::stackArrayPeek);
    connect(btnArrayClear, &QPushButton::clicked, this, &MainWindow::stackArrayClear);
    connect(btnLinkedPush, &QPushButton::clicked, this, &MainWindow::stackLinkedPush);
    connect(btnLinkedPop, &QPushButton::clicked, this, &MainWindow::stackLinkedPop);
    connect(btnLinkedPeek, &QPushButton::clicked, this, &MainWindow::stackLinkedPeek);
    connect(btnLinkedClear, &QPushButton::clicked, this, &MainWindow::stackLinkedClear);

    tabWidget->addTab(tab, "Stack");
}

void MainWindow::setupQueueTab() {
    QWidget* tab = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(tab);

    mainLayout->addWidget(createRentalForm(tab, qId, qNama, qJenis, qDurasi, qNoPosisi, false));

    QGridLayout* buttons = new QGridLayout();
    QPushButton* btnArrayEnq = new QPushButton("Array Enqueue", tab);
    QPushButton* btnArrayDeq = new QPushButton("Array Dequeue", tab);
    QPushButton* btnArrayFront = new QPushButton("Array Front", tab);
    QPushButton* btnArrayRear = new QPushButton("Array Rear", tab);
    QPushButton* btnArrayClear = new QPushButton("Array Clear", tab);
    QPushButton* btnLinkedEnq = new QPushButton("Linked Enqueue", tab);
    QPushButton* btnLinkedDeq = new QPushButton("Linked Dequeue", tab);
    QPushButton* btnLinkedFront = new QPushButton("Linked Front", tab);
    QPushButton* btnLinkedRear = new QPushButton("Linked Rear", tab);
    QPushButton* btnLinkedClear = new QPushButton("Linked Clear", tab);

    buttons->addWidget(btnArrayEnq, 0, 0);
    buttons->addWidget(btnArrayDeq, 0, 1);
    buttons->addWidget(btnArrayFront, 0, 2);
    buttons->addWidget(btnArrayRear, 0, 3);
    buttons->addWidget(btnArrayClear, 0, 4);
    buttons->addWidget(btnLinkedEnq, 1, 0);
    buttons->addWidget(btnLinkedDeq, 1, 1);
    buttons->addWidget(btnLinkedFront, 1, 2);
    buttons->addWidget(btnLinkedRear, 1, 3);
    buttons->addWidget(btnLinkedClear, 1, 4);

    QGridLayout* tables = new QGridLayout();
    queueArrayTable = createRentalTable(tab);
    queueLinkedTable = createRentalTable(tab);
    tables->addWidget(new QLabel("Queue Array Circular", tab), 0, 0);
    tables->addWidget(new QLabel("Queue Linked List", tab), 0, 1);
    tables->addWidget(queueArrayTable, 1, 0);
    tables->addWidget(queueLinkedTable, 1, 1);

    mainLayout->addLayout(buttons);
    mainLayout->addLayout(tables);

    connect(btnArrayEnq, &QPushButton::clicked, this, &MainWindow::queueArrayEnqueue);
    connect(btnArrayDeq, &QPushButton::clicked, this, &MainWindow::queueArrayDequeue);
    connect(btnArrayFront, &QPushButton::clicked, this, &MainWindow::queueArrayFront);
    connect(btnArrayRear, &QPushButton::clicked, this, &MainWindow::queueArrayRear);
    connect(btnArrayClear, &QPushButton::clicked, this, &MainWindow::queueArrayClear);
    connect(btnLinkedEnq, &QPushButton::clicked, this, &MainWindow::queueLinkedEnqueue);
    connect(btnLinkedDeq, &QPushButton::clicked, this, &MainWindow::queueLinkedDequeue);
    connect(btnLinkedFront, &QPushButton::clicked, this, &MainWindow::queueLinkedFront);
    connect(btnLinkedRear, &QPushButton::clicked, this, &MainWindow::queueLinkedRear);
    connect(btnLinkedClear, &QPushButton::clicked, this, &MainWindow::queueLinkedClear);

    tabWidget->addTab(tab, "Queue");
}

void MainWindow::setupRecursiveTab() {
    QWidget* tab = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(tab);

    QGridLayout* buttons = new QGridLayout();
    QPushButton* btnDisplay = new QPushButton("Display Pelanggan Rekursif", tab);
    QPushButton* btnTotal = new QPushButton("Hitung Total Pendapatan Rekursif", tab);
    buttons->addWidget(btnDisplay, 0, 0);
    buttons->addWidget(btnTotal, 0, 1);

    recursiveOutput = new QTextEdit(tab);
    recursiveOutput->setReadOnly(true);

    layout->addLayout(buttons);
    layout->addWidget(recursiveOutput);

    connect(btnDisplay, &QPushButton::clicked, this, &MainWindow::recursiveDisplayPelanggan);
    connect(btnTotal, &QPushButton::clicked, this, &MainWindow::recursiveTotalPendapatan);

    tabWidget->addTab(tab, "Recursive");
}

void MainWindow::setupSortingTab() {
    QWidget* tab = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(tab);

    QGroupBox* control = new QGroupBox("Pengaturan Sorting", tab);
    QGridLayout* grid = new QGridLayout(control);

    sortAlgo = new QComboBox(control);
    sortAlgo->addItems(QStringList() << "Bubble Sort" << "Selection Sort" << "Insertion Sort");

    sortField = new QComboBox(control);
    sortField->addItems(QStringList() << "ID" << "Nama" << "Total Bayar");

    QPushButton* btnLoad = new QPushButton("Ambil Data dari Pelanggan", control);
    QPushButton* btnSort = new QPushButton("Urutkan", control);

    grid->addWidget(new QLabel("Algoritma:"), 0, 0);
    grid->addWidget(sortAlgo, 0, 1);
    grid->addWidget(new QLabel("Field:"), 0, 2);
    grid->addWidget(sortField, 0, 3);
    grid->addWidget(btnLoad, 1, 0, 1, 2);
    grid->addWidget(btnSort, 1, 2, 1, 2);

    QGridLayout* tables = new QGridLayout();
    sortBeforeTable = createRentalTable(tab);
    sortAfterTable = createRentalTable(tab);
    tables->addWidget(new QLabel("Sebelum Sorting", tab), 0, 0);
    tables->addWidget(new QLabel("Sesudah Sorting", tab), 0, 1);
    tables->addWidget(sortBeforeTable, 1, 0);
    tables->addWidget(sortAfterTable, 1, 1);

    layout->addWidget(control);
    layout->addLayout(tables);

    connect(btnLoad, &QPushButton::clicked, this, &MainWindow::loadSortingData);
    connect(btnSort, &QPushButton::clicked, this, &MainWindow::sortData);

    tabWidget->addTab(tab, "Sorting");
}

void MainWindow::setupSearchingTab() {
    QWidget* tab = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(tab);

    QGroupBox* box = new QGroupBox("Input Searching", tab);
    QGridLayout* grid = new QGridLayout(box);

    searchIdInput = new QLineEdit(box);
    searchIdInput->setPlaceholderText("Masukkan ID yang dicari");

    QPushButton* btnSeqArray = new QPushButton("Sequential Search Array", box);
    QPushButton* btnSeqLinked = new QPushButton("Sequential Search Linked List", box);
    QPushButton* btnBinary = new QPushButton("Binary Search Array", box);

    grid->addWidget(new QLabel("ID:"), 0, 0);
    grid->addWidget(searchIdInput, 0, 1, 1, 3);
    grid->addWidget(btnSeqArray, 1, 0);
    grid->addWidget(btnSeqLinked, 1, 1);
    grid->addWidget(btnBinary, 1, 2);

    searchOutput = new QTextEdit(tab);
    searchOutput->setReadOnly(true);

    layout->addWidget(box);
    layout->addWidget(searchOutput);

    connect(btnSeqArray, &QPushButton::clicked, this, &MainWindow::searchSequentialArray);
    connect(btnSeqLinked, &QPushButton::clicked, this, &MainWindow::searchSequentialLinked);
    connect(btnBinary, &QPushButton::clicked, this, &MainWindow::searchBinaryArray);

    tabWidget->addTab(tab, "Searching");
}

void MainWindow::setupFileTab() {
    QWidget* tab = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(tab);

    QGroupBox* box = new QGroupBox("Save / Load File", tab);
    QGridLayout* grid = new QGridLayout(box);

    filePathInput = new QLineEdit(box);
    filePathInput->setText("data_pelanggan.txt");

    QPushButton* btnBrowse = new QPushButton("Browse", box);
    QPushButton* btnSaveP = new QPushButton("Save Pelanggan", box);
    QPushButton* btnLoadP = new QPushButton("Load Pelanggan", box);
    QPushButton* btnSaveT = new QPushButton("Save Transaksi", box);
    QPushButton* btnLoadT = new QPushButton("Load Transaksi", box);

    grid->addWidget(new QLabel("File Path:"), 0, 0);
    grid->addWidget(filePathInput, 0, 1, 1, 3);
    grid->addWidget(btnBrowse, 0, 4);
    grid->addWidget(btnSaveP, 1, 0);
    grid->addWidget(btnLoadP, 1, 1);
    grid->addWidget(btnSaveT, 1, 2);
    grid->addWidget(btnLoadT, 1, 3);

    QLabel* note = new QLabel(
        "Format file: ID;Nama;JenisPS;Durasi;TotalBayar\n"
        "Contoh: 1;Budi;PS5;2;20000",
        tab
    );

    layout->addWidget(box);
    layout->addWidget(note);
    layout->addStretch();

    connect(btnBrowse, &QPushButton::clicked, this, &MainWindow::browseFilePath);
    connect(btnSaveP, &QPushButton::clicked, this, &MainWindow::savePelanggan);
    connect(btnLoadP, &QPushButton::clicked, this, &MainWindow::loadPelanggan);
    connect(btnSaveT, &QPushButton::clicked, this, &MainWindow::saveTransaksi);
    connect(btnLoadT, &QPushButton::clicked, this, &MainWindow::loadTransaksi);

    tabWidget->addTab(tab, "Save Load");
}

void MainWindow::setupOutputTab() {
    QWidget* tab = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(tab);

    outputLog = new QTextEdit(tab);
    outputLog->setReadOnly(true);
    outputLog->setPlaceholderText("Log program tampil di sini...");

    layout->addWidget(outputLog);
    tabWidget->addTab(tab, "Output Log");
}

Rental MainWindow::readRental(QLineEdit* id, QLineEdit* nama, QComboBox* jenis, QLineEdit* durasi, bool* ok) {
    *ok = false;

    bool idOk = false;
    bool durasiOk = false;
    int idValue = id->text().toInt(&idOk);
    int durasiValue = durasi->text().toInt(&durasiOk);
    QString namaValue = nama->text().trimmed();
    QString jenisValue = jenis->currentText();

    if (!idOk || idValue <= 0) {
        QMessageBox::warning(this, "Input Salah", "ID harus berupa angka lebih dari 0.");
        return Rental{};
    }

    if (namaValue.isEmpty()) {
        QMessageBox::warning(this, "Input Salah", "Nama tidak boleh kosong.");
        return Rental{};
    }

    if (!durasiOk || durasiValue <= 0) {
        QMessageBox::warning(this, "Input Salah", "Durasi harus berupa angka lebih dari 0.");
        return Rental{};
    }

    Rental data(idValue, namaValue, jenisValue, durasiValue);
    data.totalBayar = hitungBiaya(data.jenisPS, data.durasiJam);
    *ok = true;
    return data;
}

void MainWindow::addRentalRow(QTableWidget* table, const Rental& data) {
    int row = table->rowCount();
    table->insertRow(row);

    table->setItem(row, 0, new QTableWidgetItem(QString::number(data.id)));
    table->setItem(row, 1, new QTableWidgetItem(data.nama));
    table->setItem(row, 2, new QTableWidgetItem(data.jenisPS));
    table->setItem(row, 3, new QTableWidgetItem(QString::number(data.durasiJam)));
    table->setItem(row, 4, new QTableWidgetItem(QString::number(data.totalBayar)));
}

void MainWindow::fillTableFromArray(QTableWidget* table, const Rental* arr, int n) {
    table->setRowCount(0);

    for (int i = 0; i < n; i++) {
        addRentalRow(table, arr[i]);
    }
}

void MainWindow::refreshSinglyTable() {
    sTable->setRowCount(0);
    NodeSingly* current = dataPelanggan.getHead();

    while (current != nullptr) {
        addRentalRow(sTable, current->data);
        current = current->next;
    }
}

void MainWindow::refreshDoublyForwardTable() {
    dTable->setRowCount(0);
    NodeDoubly* current = dataTransaksi.getHead();

    while (current != nullptr) {
        addRentalRow(dTable, current->data);
        current = current->next;
    }
}

void MainWindow::refreshDoublyBackwardTable() {
    dTable->setRowCount(0);
    NodeDoubly* current = dataTransaksi.getTail();

    while (current != nullptr) {
        addRentalRow(dTable, current->data);
        current = current->prev;
    }
}

void MainWindow::refreshStackTables() {
    stackArrayTable->setRowCount(0);
    for (int i = 0; i < stackArr.count(); i++) {
        int row = stackArrayTable->rowCount();
        stackArrayTable->insertRow(row);
        stackArrayTable->setItem(row, 0, new QTableWidgetItem(stackArr.valueFromTop(i)));
    }

    stackLinkedTable->setRowCount(0);
    NodeStack* current = stackLink.getTop();
    while (current != nullptr) {
        int row = stackLinkedTable->rowCount();
        stackLinkedTable->insertRow(row);
        stackLinkedTable->setItem(row, 0, new QTableWidgetItem(current->aksi));
        current = current->next;
    }
}

void MainWindow::refreshQueueTables() {
    queueArrayTable->setRowCount(0);
    for (int i = 0; i < queueArr.count(); i++) {
        addRentalRow(queueArrayTable, queueArr.valueAt(i));
    }

    queueLinkedTable->setRowCount(0);
    NodeQueue* current = queueLink.getFrontNode();
    while (current != nullptr) {
        addRentalRow(queueLinkedTable, current->data);
        current = current->next;
    }
}

void MainWindow::logMessage(const QString& message) {
    if (outputLog != nullptr) {
        outputLog->append(message);
    }
}

bool MainWindow::confirmClear(const QString& message) {
    QMessageBox::StandardButton result = QMessageBox::question(this, "Konfirmasi", message);
    return result == QMessageBox::Yes;
}

void MainWindow::pushAction(const QString& action) {
    stackArr.push(action);
    stackLink.push(action);
    refreshStackTables();
}

void MainWindow::sInsertAwal() {
    bool ok = false;
    Rental data = readRental(sId, sNama, sJenis, sDurasi, &ok);
    if (!ok) return;
    if (dataPelanggan.containsId(data.id)) {
        QMessageBox::warning(this, "Duplikat", "ID pelanggan sudah ada.");
        return;
    }

    dataPelanggan.insertAwal(data);
    refreshSinglyTable();
    pushAction("Singly insert awal: " + data.nama);
    logMessage("Insert awal berhasil: " + rentalToText(data));
    resetAllInputs();
}

void MainWindow::sInsertAkhir() {
    bool ok = false;
    Rental data = readRental(sId, sNama, sJenis, sDurasi, &ok);
    if (!ok) return;
    if (dataPelanggan.containsId(data.id)) {
        QMessageBox::warning(this, "Duplikat", "ID pelanggan sudah ada.");
        return;
    }

    dataPelanggan.insertAkhir(data);
    refreshSinglyTable();
    pushAction("Singly insert akhir: " + data.nama);
    logMessage("Insert akhir berhasil: " + rentalToText(data));
    resetAllInputs();
}

void MainWindow::sInsertPosisi() {
    bool posisiOk = false;
    int posisi = sPosisi->text().toInt(&posisiOk);

    if (!posisiOk || posisi <= 0) {
        QMessageBox::warning(this, "Input Salah", "Posisi harus berupa angka lebih dari 0.");
        return;
    }

    bool ok = false;
    Rental data = readRental(sId, sNama, sJenis, sDurasi, &ok);
    if (!ok) return;
    if (dataPelanggan.containsId(data.id)) {
        QMessageBox::warning(this, "Duplikat", "ID pelanggan sudah ada.");
        return;
    }

    if (!dataPelanggan.insertPosisi(data, posisi)) {
        QMessageBox::warning(this, "Gagal", "Posisi tidak valid.");
        return;
    }

    refreshSinglyTable();
    pushAction("Singly insert posisi " + QString::number(posisi) + ": " + data.nama);
    logMessage("Insert posisi berhasil: " + rentalToText(data));
    resetAllInputs();
}

void MainWindow::sDeleteId() {
    bool idOk = false;
    int id = sId->text().toInt(&idOk);

    if (!idOk || id <= 0) {
        QMessageBox::warning(this, "Input Salah", "Masukkan ID valid untuk dihapus.");
        return;
    }

    if (!dataPelanggan.deleteById(id)) {
        QMessageBox::warning(this, "Tidak Ditemukan", "Data pelanggan tidak ditemukan.");
        return;
    }

    refreshSinglyTable();
    pushAction("Singly delete ID: " + QString::number(id));
    logMessage("Delete pelanggan berhasil, ID: " + QString::number(id));
    resetAllInputs();
}

void MainWindow::sDisplay() {
    refreshSinglyTable();
    logMessage("Traversal singly linked list ditampilkan. Total data: " + QString::number(dataPelanggan.count()));
}

void MainWindow::sClear() {
    if (dataPelanggan.isEmpty()) {
        QMessageBox::information(this, "Info", "Data pelanggan masih kosong.");
        return;
    }

    if (!confirmClear("Yakin hapus semua data pelanggan?")) return;

    dataPelanggan.clear();
    refreshSinglyTable();
    pushAction("Singly clear semua data");
    logMessage("Semua data pelanggan dihapus.");
}

void MainWindow::dTambahTransaksi() {
    bool ok = false;
    Rental data = readRental(dId, dNama, dJenis, dDurasi, &ok);
    if (!ok) return;
    if (dataTransaksi.containsId(data.id)) {
        QMessageBox::warning(this, "Duplikat", "ID transaksi sudah ada.");
        return;
    }

    dataTransaksi.insertAkhir(data);
    refreshDoublyForwardTable();
    pushAction("Doubly tambah transaksi: " + data.nama);
    logMessage("Transaksi ditambahkan: " + rentalToText(data));
    resetAllInputs();
}

void MainWindow::dDeleteId() {
    bool idOk = false;
    int id = dId->text().toInt(&idOk);

    if (!idOk || id <= 0) {
        QMessageBox::warning(this, "Input Salah", "Masukkan ID transaksi yang valid.");
        return;
    }

    if (!dataTransaksi.deleteById(id)) {
        QMessageBox::warning(this, "Tidak Ditemukan", "Transaksi tidak ditemukan.");
        return;
    }

    refreshDoublyForwardTable();
    pushAction("Doubly delete transaksi ID: " + QString::number(id));
    logMessage("Delete transaksi berhasil, ID: " + QString::number(id));
    resetAllInputs();
}

void MainWindow::dDisplayMaju() {
    refreshDoublyForwardTable();
    logMessage("Traversal doubly maju ditampilkan.");
}

void MainWindow::dDisplayMundur() {
    refreshDoublyBackwardTable();
    logMessage("Traversal doubly mundur ditampilkan.");
}

void MainWindow::dClear() {
    if (dataTransaksi.isEmpty()) {
        QMessageBox::information(this, "Info", "Data transaksi masih kosong.");
        return;
    }
    if (!confirmClear("Yakin hapus semua data transaksi?")) return;

    dataTransaksi.clear();
    refreshDoublyForwardTable();
    pushAction("Doubly clear semua transaksi");
    logMessage("Semua transaksi dihapus.");
}

void MainWindow::stackArrayPush() {
    QString aksi = stackInput->text().trimmed();
    if (aksi.isEmpty()) {
        QMessageBox::warning(this, "Input Salah", "Aksi stack tidak boleh kosong.");
        return;
    }

    if (!stackArr.push(aksi)) {
        QMessageBox::warning(this, "Stack Full", "Stack array penuh.");
        return;
    }

    refreshStackTables();
    logMessage("Stack array push: " + aksi);
    stackInput->clear();
}

void MainWindow::stackArrayPop() {
    QString aksi;
    if (!stackArr.pop(aksi)) {
        QMessageBox::warning(this, "Stack Kosong", "Stack array masih kosong.");
        return;
    }

    refreshStackTables();
    logMessage("Stack array pop: " + aksi);
}

void MainWindow::stackArrayPeek() {
    QString aksi;
    if (!stackArr.peek(aksi)) {
        QMessageBox::warning(this, "Stack Kosong", "Stack array masih kosong.");
        return;
    }

    QMessageBox::information(this, "Peek Stack Array", aksi);
    logMessage("Stack array peek: " + aksi);
}

void MainWindow::stackArrayClear() {
    stackArr.clear();
    refreshStackTables();
    logMessage("Stack array dibersihkan.");
}

void MainWindow::stackLinkedPush() {
    QString aksi = stackInput->text().trimmed();
    if (aksi.isEmpty()) {
        QMessageBox::warning(this, "Input Salah", "Aksi stack tidak boleh kosong.");
        return;
    }

    stackLink.push(aksi);
    refreshStackTables();
    logMessage("Stack linked push: " + aksi);
    stackInput->clear();
}

void MainWindow::stackLinkedPop() {
    QString aksi;
    if (!stackLink.pop(aksi)) {
        QMessageBox::warning(this, "Stack Kosong", "Stack linked list masih kosong.");
        return;
    }

    refreshStackTables();
    logMessage("Stack linked pop: " + aksi);
}

void MainWindow::stackLinkedPeek() {
    QString aksi;
    if (!stackLink.peek(aksi)) {
        QMessageBox::warning(this, "Stack Kosong", "Stack linked list masih kosong.");
        return;
    }

    QMessageBox::information(this, "Peek Stack Linked", aksi);
    logMessage("Stack linked peek: " + aksi);
}

void MainWindow::stackLinkedClear() {
    stackLink.clear();
    refreshStackTables();
    logMessage("Stack linked list dibersihkan.");
}

void MainWindow::queueArrayEnqueue() {
    bool ok = false;
    Rental data = readRental(qId, qNama, qJenis, qDurasi, &ok);
    if (!ok) return;

    if (!queueArr.enqueue(data)) {
        QMessageBox::warning(this, "Queue Full", "Queue array penuh.");
        return;
    }

    refreshQueueTables();
    pushAction("Queue array enqueue: " + data.nama);
    logMessage("Queue array enqueue: " + rentalToText(data));
    resetAllInputs();
}

void MainWindow::queueArrayDequeue() {
    Rental data;
    if (!queueArr.dequeue(data)) {
        QMessageBox::warning(this, "Queue Kosong", "Queue array masih kosong.");
        return;
    }

    refreshQueueTables();
    pushAction("Queue array dequeue: " + data.nama);
    logMessage("Queue array dequeue: " + rentalToText(data));
}

void MainWindow::queueArrayFront() {
    Rental data;
    if (!queueArr.front(data)) {
        QMessageBox::warning(this, "Queue Kosong", "Queue array masih kosong.");
        return;
    }

    QMessageBox::information(this, "Front Queue Array", rentalToText(data));
}

void MainWindow::queueArrayRear() {
    Rental data;
    if (!queueArr.rear(data)) {
        QMessageBox::warning(this, "Queue Kosong", "Queue array masih kosong.");
        return;
    }

    QMessageBox::information(this, "Rear Queue Array", rentalToText(data));
}

void MainWindow::queueArrayClear() {
    queueArr.clear();
    refreshQueueTables();
    logMessage("Queue array dibersihkan.");
}

void MainWindow::queueLinkedEnqueue() {
    bool ok = false;
    Rental data = readRental(qId, qNama, qJenis, qDurasi, &ok);
    if (!ok) return;

    queueLink.enqueue(data);
    refreshQueueTables();
    pushAction("Queue linked enqueue: " + data.nama);
    logMessage("Queue linked enqueue: " + rentalToText(data));
    resetAllInputs();
}

void MainWindow::queueLinkedDequeue() {
    Rental data;
    if (!queueLink.dequeue(data)) {
        QMessageBox::warning(this, "Queue Kosong", "Queue linked list masih kosong.");
        return;
    }

    refreshQueueTables();
    pushAction("Queue linked dequeue: " + data.nama);
    logMessage("Queue linked dequeue: " + rentalToText(data));
}

void MainWindow::queueLinkedFront() {
    Rental data;
    if (!queueLink.front(data)) {
        QMessageBox::warning(this, "Queue Kosong", "Queue linked list masih kosong.");
        return;
    }

    QMessageBox::information(this, "Front Queue Linked", rentalToText(data));
}

void MainWindow::queueLinkedRear() {
    Rental data;
    if (!queueLink.rear(data)) {
        QMessageBox::warning(this, "Queue Kosong", "Queue linked list masih kosong.");
        return;
    }

    QMessageBox::information(this, "Rear Queue Linked", rentalToText(data));
}

void MainWindow::queueLinkedClear() {
    queueLink.clear();
    refreshQueueTables();
    logMessage("Queue linked list dibersihkan.");
}

void MainWindow::recursiveDisplayPelanggan() {
    QString result = Recursive::displaySingly(dataPelanggan.getHead());
    if (result.isEmpty()) {
        result = "Data pelanggan masih kosong.";
    }

    recursiveOutput->setPlainText(result);
    logMessage("Recursive display pelanggan dijalankan.");
}

void MainWindow::recursiveTotalPendapatan() {
    int total = Recursive::totalPendapatan(dataTransaksi.getHead());
    recursiveOutput->setPlainText("Total pendapatan dari doubly linked list secara rekursif: Rp" + QString::number(total));
    logMessage("Recursive total pendapatan dijalankan.");
}

void MainWindow::loadSortingData() {
    sortingCount = dataPelanggan.toArray(sortingCache, QUEUE_MAX);
    fillTableFromArray(sortBeforeTable, sortingCache, sortingCount);
    sortAfterTable->setRowCount(0);
    logMessage("Data sorting diambil dari data pelanggan: " + QString::number(sortingCount) + " data.");
}

void MainWindow::sortData() {
    if (sortingCount == 0) {
        loadSortingData();
    }

    if (sortingCount == 0) {
        QMessageBox::warning(this, "Data Kosong", "Data pelanggan masih kosong.");
        return;
    }

    Rental arr[QUEUE_MAX];
    for (int i = 0; i < sortingCount; i++) {
        arr[i] = sortingCache[i];
    }

    int field = sortField->currentIndex();
    int algo = sortAlgo->currentIndex();

    if (algo == 0) {
        Sorting::bubbleSort(arr, sortingCount, field);
    } else if (algo == 1) {
        Sorting::selectionSort(arr, sortingCount, field);
    } else {
        Sorting::insertionSort(arr, sortingCount, field);
    }

    fillTableFromArray(sortAfterTable, arr, sortingCount);
    logMessage("Sorting selesai: " + sortAlgo->currentText() + " berdasarkan " + sortField->currentText());
}

void MainWindow::searchSequentialArray() {
    bool idOk = false;
    int id = searchIdInput->text().toInt(&idOk);
    if (!idOk || id <= 0) {
        QMessageBox::warning(this, "Input Salah", "Masukkan ID valid.");
        return;
    }

    Rental arr[QUEUE_MAX];
    int n = dataPelanggan.toArray(arr, QUEUE_MAX);
    int index = Searching::sequentialArrayById(arr, n, id);

    if (index == -1) {
        searchOutput->setPlainText("Sequential array: data tidak ditemukan.");
    } else {
        searchOutput->setPlainText("Sequential array: data ditemukan pada index " + QString::number(index) + "\n" + rentalToText(arr[index]));
    }
}

void MainWindow::searchSequentialLinked() {
    bool idOk = false;
    int id = searchIdInput->text().toInt(&idOk);
    if (!idOk || id <= 0) {
        QMessageBox::warning(this, "Input Salah", "Masukkan ID valid.");
        return;
    }

    Rental result;
    bool found = Searching::sequentialLinkedListById(dataPelanggan.getHead(), id, result);

    if (!found) {
        searchOutput->setPlainText("Sequential linked list: data tidak ditemukan.");
    } else {
        searchOutput->setPlainText("Sequential linked list: data ditemukan\n" + rentalToText(result));
    }
}

void MainWindow::searchBinaryArray() {
    bool idOk = false;
    int id = searchIdInput->text().toInt(&idOk);
    if (!idOk || id <= 0) {
        QMessageBox::warning(this, "Input Salah", "Masukkan ID valid.");
        return;
    }

    Rental arr[QUEUE_MAX];
    int n = dataPelanggan.toArray(arr, QUEUE_MAX);

    if (n == 0) {
        QMessageBox::warning(this, "Data Kosong", "Data pelanggan masih kosong.");
        return;
    }

    Sorting::bubbleSort(arr, n, 0);
    int index = Searching::binaryArrayById(arr, n, id);

    if (index == -1) {
        searchOutput->setPlainText("Binary search array: data tidak ditemukan.\nCatatan: array sudah diurutkan berdasarkan ID sebelum binary search.");
    } else {
        searchOutput->setPlainText("Binary search array: data ditemukan pada index " + QString::number(index) +
                                   " setelah array diurutkan berdasarkan ID.\n" + rentalToText(arr[index]));
    }
}

void MainWindow::savePelanggan() {
    QString filePath = filePathInput != nullptr ? filePathInput->text().trimmed() : "data_pelanggan.txt";
    if (filePath.isEmpty()) filePath = "data_pelanggan.txt";

    QString message;
    bool ok = FileHandler::saveSingly(filePath, dataPelanggan, message);
    logMessage(message + " File: " + filePath);

    if (!ok) {
        QMessageBox::warning(this, "Save Gagal", message);
    } else {
        QMessageBox::information(this, "Save Berhasil", message);
    }
}

void MainWindow::loadPelanggan() {
    QString filePath = filePathInput != nullptr ? filePathInput->text().trimmed() : "data_pelanggan.txt";
    if (filePath.isEmpty()) filePath = "data_pelanggan.txt";

    QString message;
    bool ok = FileHandler::loadSingly(filePath, dataPelanggan, message);
    refreshSinglyTable();
    logMessage(message + " File: " + filePath);

    if (!ok) {
        QMessageBox::warning(this, "Load Gagal", message);
    } else {
        QMessageBox::information(this, "Load Berhasil", message);
    }
}

void MainWindow::saveTransaksi() {
    QString filePath = filePathInput != nullptr ? filePathInput->text().trimmed() : "data_transaksi.txt";
    if (filePath.isEmpty()) filePath = "data_transaksi.txt";

    QString message;
    bool ok = FileHandler::saveDoubly(filePath, dataTransaksi, message);
    logMessage(message + " File: " + filePath);

    if (!ok) {
        QMessageBox::warning(this, "Save Gagal", message);
    } else {
        QMessageBox::information(this, "Save Berhasil", message);
    }
}

void MainWindow::loadTransaksi() {
    QString filePath = filePathInput != nullptr ? filePathInput->text().trimmed() : "data_transaksi.txt";
    if (filePath.isEmpty()) filePath = "data_transaksi.txt";

    QString message;
    bool ok = FileHandler::loadDoubly(filePath, dataTransaksi, message);
    refreshDoublyForwardTable();
    logMessage(message + " File: " + filePath);

    if (!ok) {
        QMessageBox::warning(this, "Load Gagal", message);
    } else {
        QMessageBox::information(this, "Load Berhasil", message);
    }
}

void MainWindow::browseFilePath() {
    QString filePath = QFileDialog::getSaveFileName(this, "Pilih File", "data_pelanggan.txt", "Text File (*.txt);;All Files (*)");

    if (!filePath.isEmpty()) {
        filePathInput->setText(filePath);
    }
}

void MainWindow::resetAllInputs() {
    QList<QLineEdit*> edits = findChildren<QLineEdit*>();
    for (QLineEdit* edit : edits) {
        if (edit != filePathInput) {
            edit->clear();
        }
    }
}

void MainWindow::tampilkanTentang() {
    QMessageBox::information(
        this,
        "Tentang Program",
        "Sistem Rental PS & Antrian Main Game\n"
        "Project UAS Struktur Data\n\n"
        "Dibuat dengan C++ Qt Widgets.\n"
        "Semua struktur data utama dibuat manual memakai struct dan pointer."
    );
}
