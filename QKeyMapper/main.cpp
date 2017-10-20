#include <QApplication>
#include "qkeymapper.h"

#ifdef DEBUG_LOGOUT_ON
#include "vld.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));

#ifdef ADJUST_PRIVILEGES
//    BOOL adjustresult = QKeyMapper::AdjustPrivileges();
//    qDebug() << "AdjustPrivileges Result:" << adjustresult;

    BOOL adjustresult = QKeyMapper::EnableDebugPrivilege();
    qDebug() << "EnableDebugPrivilege Result:" << adjustresult;
#endif

    QKeyMapper w;

    // Remove "?" Button from QDialog
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    w.setWindowFlags(flags);

    w.show();

    return a.exec();
}
