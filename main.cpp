#include "mainwindow.h"
#include "icon.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto icon = QPixmap();
    icon.loadFromData(icon_ico, icon_ico_len);
    a.setWindowIcon(QIcon(icon));
    MainWindow w;
    w.show();
    return a.exec();
}
