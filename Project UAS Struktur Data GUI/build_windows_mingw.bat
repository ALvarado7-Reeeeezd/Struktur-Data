@echo off
setlocal enabledelayedexpansion

echo ============================================
echo Build RentalPS_GUI - Windows Qt MinGW
echo ============================================

where cmake >nul 2>nul
if errorlevel 1 (
    echo [ERROR] CMake belum terinstall atau belum masuk PATH.
    echo Install Qt Creator lengkap dengan CMake, atau install CMake manual.
    pause
    exit /b 1
)

rem Jika auto-detect gagal, isi manual baris ini, contoh:
rem set "QT_DIR=C:\Qt\6.8.3\mingw_64"
rem set "MINGW_DIR=C:\Qt\Tools\mingw1310_64"

if not defined QT_DIR (
    for /d %%D in ("C:\Qt\6.*\mingw_64") do set "QT_DIR=%%~fD"
)
if not defined QT_DIR (
    for /d %%D in ("C:\Qt\6.*\mingw*_64") do set "QT_DIR=%%~fD"
)

if not defined MINGW_DIR (
    for /d %%D in ("C:\Qt\Tools\mingw*_64") do set "MINGW_DIR=%%~fD"
)

if not defined QT_DIR (
    echo [ERROR] Folder Qt MinGW tidak ketemu otomatis.
    echo Edit file build_windows_mingw.bat lalu isi QT_DIR manual.
    pause
    exit /b 1
)

if not exist "%QT_DIR%\bin\qmake.exe" (
    echo [ERROR] QT_DIR tidak valid: %QT_DIR%
    echo Pastikan folder berisi bin\qmake.exe
    pause
    exit /b 1
)

if defined MINGW_DIR (
    set "PATH=%QT_DIR%\bin;%MINGW_DIR%\bin;%PATH%"
) else (
    set "PATH=%QT_DIR%\bin;%PATH%"
)

echo QT_DIR    = %QT_DIR%
echo MINGW_DIR = %MINGW_DIR%

echo.
echo [1/2] Configure CMake...
cmake -S . -B build-windows -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="%QT_DIR%"
if errorlevel 1 (
    echo [ERROR] Configure gagal.
    pause
    exit /b 1
)

echo.
echo [2/2] Build project...
cmake --build build-windows
if errorlevel 1 (
    echo [ERROR] Build gagal.
    pause
    exit /b 1
)

echo.
echo [OK] Build berhasil.
echo Jalankan dengan: run_windows.bat
echo File exe: build-windows\RentalPS_GUI.exe
pause
