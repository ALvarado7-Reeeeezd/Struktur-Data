
## Fitur

1. Singly Linked List - Data pelanggan
2. Doubly Linked List - Riwayat transaksi
3. Stack array dan stack linked list
4. Queue array circular dan queue linked list
5. Recursive minimal 2 fungsi
6. Sorting 3 algoritma: Bubble, Selection, Insertion
7. Searching: Sequential dan Binary Search
8. Save / Load file TXT

## Build di Fedora

Install dependency:

```bash
sudo dnf install gcc-c++ make cmake ninja-build gdb git qt-creator qt6-qtbase-devel qt6-qttools-devel
```

Build:

```bash
cd Project_UAS_Struktur_Data_GUI_Final
rm -rf build
cmake -S . -B build -G Ninja
cmake --build build
./build/RentalPS_GUI
```

Kalau `ninja` belum ada:

```bash
sudo dnf install ninja-build
```

Atau build tanpa Ninja:

```bash
cmake -S . -B build
cmake --build build
./build/RentalPS_GUI
```

## Cara Demo Singkat

1. Tab Singly List: tambah 3 pelanggan, coba insert awal, akhir, posisi, delete ID, display.
2. Tab Doubly List: tambah transaksi, display maju dan mundur.
3. Tab Stack: push, pop, peek untuk stack array dan linked list.
4. Tab Queue: enqueue, dequeue, front, rear untuk queue array dan linked list.
5. Tab Recursive: display pelanggan rekursif dan total pendapatan rekursif.
6. Tab Sorting: ambil data pelanggan, pilih algoritma, klik urutkan.
7. Tab Searching: cari ID dengan sequential array, sequential linked list, dan binary search.
8. Tab Save Load: save dan load data ke file txt.

## Catatan

- Struktur data dibuat manual, bukan memakai `std::list`, `std::stack`, atau `std::queue`.
- Memory linked list, stack linked list, dan queue linked list dibersihkan memakai `delete`.
- Data file menggunakan format: `ID;Nama;JenisPS;Durasi;TotalBayar`.
