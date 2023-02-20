#include <QApplication>
#include "qkeymapper.h"
#include "qkeymapper_worker.h"

#ifdef DEBUG_LOGOUT_ON
//#include "vld.h"
#endif

int main(int argc, char *argv[])
{
    if (QDir::currentPath() != QCoreApplication::applicationDirPath()) {
        QDir::setCurrent(QCoreApplication::applicationDirPath());
    }

    int nScreenWidth = ::GetSystemMetrics(SM_CXSCREEN);
    HWND hwd = ::GetDesktopWindow();
    HDC hdc = ::GetDC(hwd);
    int width = GetDeviceCaps(hdc, DESKTOPHORZRES);
    double dWidth = (double)width;
    double dScreenWidth = (double)nScreenWidth;
    double scale = dWidth / dScreenWidth;

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Round);
#elif (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)) && (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    if (scale < 1.10) {
        qDebug() << "Original screen scale ->" << scale << ", set QT_SCALE_FACTOR to 1.5";
        qputenv("QT_SCALE_FACTOR", "1.5");
    }
    else {
        qDebug() << "Original screen scale ->" << scale << ", do not need to set QT_SCALE_FACTOR";
    }

    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    qSetMessagePattern("%{time [hh:mm:ss.zzz]} %{message}");

#ifdef ADJUST_PRIVILEGES
//    BOOL adjustresult = QKeyMapper::AdjustPrivileges();
//    qDebug() << "AdjustPrivileges Result:" << adjustresult;

    BOOL adjustresult = QKeyMapper::EnableDebugPrivilege();
    qDebug() << "EnableDebugPrivilege Result:" << adjustresult;
#endif
    QThread::currentThread()->setObjectName("QKeyMapper");

    QKeyMapper_Worker * const keymapper_worker = QKeyMapper_Worker::getInstance();
    // Move Checksumer to a sub thread
    QThread * const workerThread = new QThread();
    keymapper_worker->moveToThread(workerThread);
    workerThread->setObjectName("QKeyMapper_Worker");
    QObject::connect(workerThread, SIGNAL(started()), keymapper_worker, SLOT(threadStarted()));
    workerThread->start();

    QKeyMapper w;

    // Remove "?" Button from QDialog
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    w.setWindowFlags(flags);

    if (true == w.getAutoStartMappingStatus()) {
#ifdef DEBUG_LOGOUT_ON
        qDebug() << "Auto Start Mapping = TRUE, hide QKeyMapper window at startup.";
#endif
    }
    else {
        w.show();
    }

    return a.exec();
}
