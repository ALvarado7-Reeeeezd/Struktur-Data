@echo off
setlocal

rem Jika Qt DLL belum terbaca, isi QT_DIR manual seperti di build script.
rem set "QT_DIR=C:\Qt\6.8.3\mingw_64"

if not defined QT_DIR (
    for /d %%D in ("C:\Qt\6.*\mingw_64") do set "QT_DIR=%%~fD"
)
if not defined QT_DIR (
    for /d %%D in ("C:\Qt\6.*\mingw*_64") do set "QT_DIR=%%~fD"
)

if defined QT_DIR set "PATH=%QT_DIR%\bin;%PATH%"

if not exist "build-windows\RentalPS_GUI.exe" (
    echo [ERROR] build-windows\RentalPS_GUI.exe belum ada.
    echo Jalankan build_windows_mingw.bat dulu.
    pause
    exit /b 1
)

build-windows\RentalPS_GUI.exe
