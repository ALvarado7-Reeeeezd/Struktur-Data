# Project UAS Struktur Data - Versi Windows Qt GUI

Ini adalah versi Windows-ready dari project **Sistem Rental PS & Antrian Main Game** berbasis **C++ Qt Widgets**.

Source code utama tetap memakai Qt GUI:

- `src/main.cpp`
- `src/mainwindow.cpp`
- `src/singlylist.cpp`
- `src/doublylist.cpp`
- `src/stackdata.cpp`
- `src/queuedata.cpp`
- `src/sorting.cpp`
- `src/searching.cpp`
- `src/recursive.cpp`
- `src/filehandler.cpp`
- folder `include/`

Folder build Linux, file Ninja Linux, cache Linux, dan executable Linux tidak disertakan karena tidak cocok untuk Windows.

---

## Yang perlu diinstall di Windows

### Opsi paling mudah: Qt Creator

Install lewat **Qt Online Installer** dari website Qt.

Saat memilih komponen, centang minimal:

1. **Qt Creator**
2. **Qt 6.x for MinGW 64-bit**
3. **MinGW 64-bit** yang satu paket dengan Qt
4. **CMake**
5. **Ninja**

Contoh struktur setelah install biasanya seperti ini:

```text
C:\Qt\6.8.3\mingw_64
C:\Qt\Tools\mingw1310_64
```

Versinya bisa beda, tidak masalah. Yang penting Qt dan MinGW-nya satu paket/sesuai.

---

## Cara menjalankan dengan Qt Creator

1. Buka **Qt Creator**.
2. Pilih **File -> Open File or Project**.
3. Pilih file:

```text
CMakeLists.txt
```

4. Pilih kit **Desktop Qt 6.x MinGW 64-bit**.
5. Klik **Configure Project**.
6. Klik tombol **Run**.

Ini cara paling aman untuk Windows.

---

## Cara menjalankan lewat Command Prompt / PowerShell

Buka terminal di folder project ini, lalu jalankan:

```bat
build_windows_mingw.bat
```

Setelah build berhasil, jalankan:

```bat
run_windows.bat
```

Kalau ingin membuat folder deploy berisi `.exe` + DLL Qt yang bisa dipindahkan ke laptop lain, jalankan:

```bat
deploy_windows.bat
```

Hasil deploy ada di folder:

```text
deploy\
```

---

## Kalau build gagal

### 1. Error: Could not find Qt6

Artinya CMake belum tahu lokasi Qt. Edit file `build_windows_mingw.bat`, lalu isi manual:

```bat
set "QT_DIR=C:\Qt\6.8.3\mingw_64"
```

Sesuaikan dengan folder Qt di laptop kamu.

### 2. Error: g++ not found

Artinya MinGW belum masuk PATH. Edit file `build_windows_mingw.bat`, lalu isi manual:

```bat
set "MINGW_DIR=C:\Qt\Tools\mingw1310_64"
```

Sesuaikan dengan folder MinGW di laptop kamu.

### 3. Jangan compile manual pakai `g++ *.cpp`

Project ini adalah Qt GUI, jadi tidak cukup compile manual seperti program console. Harus lewat **CMake/Qt Creator** supaya Qt Widgets ikut ter-link.

---

## Catatan

File ini adalah versi Windows untuk project Qt GUI asli. Kalau dosen meminta Dev-C++ biasa, gunakan versi console terpisah karena Dev-C++ tidak cocok untuk Qt GUI langsung.
