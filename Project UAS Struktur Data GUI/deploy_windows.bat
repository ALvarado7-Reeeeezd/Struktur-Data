@echo off
setlocal

rem Script ini membuat folder deploy berisi exe + DLL Qt.
rem Jalankan setelah build_windows_mingw.bat berhasil.

if not defined QT_DIR (
    for /d %%D in ("C:\Qt\6.*\mingw_64") do set "QT_DIR=%%~fD"
)
if not defined QT_DIR (
    for /d %%D in ("C:\Qt\6.*\mingw*_64") do set "QT_DIR=%%~fD"
)

if not defined QT_DIR (
    echo [ERROR] Folder Qt tidak ketemu. Isi QT_DIR manual di script ini.
    pause
    exit /b 1
)

set "PATH=%QT_DIR%\bin;%PATH%"

if not exist "build-windows\RentalPS_GUI.exe" (
    echo [ERROR] build-windows\RentalPS_GUI.exe belum ada.
    echo Jalankan build_windows_mingw.bat dulu.
    pause
    exit /b 1
)

if exist deploy rmdir /s /q deploy
mkdir deploy
copy "build-windows\RentalPS_GUI.exe" "deploy\RentalPS_GUI.exe" >nul

windeployqt "deploy\RentalPS_GUI.exe"
if errorlevel 1 (
    echo [ERROR] windeployqt gagal.
    pause
    exit /b 1
)

echo [OK] Deploy selesai. Cek folder deploy\
pause
