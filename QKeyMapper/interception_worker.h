#ifndef INTERCEPTION_WORKER_H
#define INTERCEPTION_WORKER_H

#include <QObject>
#include <interception.h>

#include "qkeymapper.h"
#include "qkeymapper_worker.h"

class Interception_Worker : public QObject
{
    Q_OBJECT
public:
    explicit Interception_Worker(QObject *parent = Q_NULLPTR);
    ~Interception_Worker();

    static Interception_Worker *getInstance()
    {
        static Interception_Worker m_instance;
        return &m_instance;
    }

    enum Interception_State
    {
        INTERCEPTION_UNAVAILABLE = 0,
        INTERCEPTION_REBOOTREQUIRED,
        INTERCEPTION_AVAILABLE,
    };
    Q_ENUM(Interception_State)

signals:

public slots:
    void InterceptionThreadStarted(void);
    bool doLoadInterception(void);
    void doUnloadInterception(void);
    void startInterception(void);
    void stopInterception(void);

public:
    static bool isInterceptionDriverFileExist(void);
    static Interception_State getInterceptionState(void);
    static QString getDeviceNameByHardwareID(const QString& hardwareID);
    static InterceptionContext getInterceptionContext(void);
    static QList<InputDevice> getKeyboardDeviceList(void);
    static QList<InputDevice> getMouseDeviceList(void);
    static QString getHardwareId(InterceptionDevice device);
    static QString getDeviceName(InterceptionDevice device);

    static InterceptionContext s_InterceptionContext;
    static QAtomicBool s_InterceptStart;
};

#endif // INTERCEPTION_WORKER_H
