#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Sistem Rental PS & Antrian Main Game");
    window.resize(1200, 760);
    window.show();

    return app.exec();
}
