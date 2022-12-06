#ifndef QKEYMAPPER_H
#define QKEYMAPPER_H

#include <QDialog>
#include <QDebug>
#include <QMetaEnum>
#include <QMessageBox>
#include <QTimer>
#include <QTimerEvent>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QHash>
#include <QtWin>
#include <QStyleFactory>
#include <QFontDatabase>
#include <QStyledItemDelegate>
#include <QComboBox>
#include <QCheckBox>
#include <QKeyEvent>
#include <QHotkey>
#include <windows.h>
#include <tlhelp32.h>
#include <Psapi.h>
#include <tchar.h>
#include <string.h>
//#include <QKeyEvent>
//#include <QProcess>
//#include <QTextCodec>
#include <dinput.h>

namespace Ui {
class QKeyMapper;
}

typedef struct
{
    QString FileName;
    QString PID;
    QString WindowTitle;
    QString FilePath;
    QIcon   WindowIcon;
}MAP_PROCESSINFO;

typedef HRESULT(WINAPI* GetDeviceStateT)(IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData);
typedef HRESULT(WINAPI* GetDeviceDataT)(IDirectInputDevice8*, DWORD, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);

#define SEPARATOR_STR   (" + ")

typedef struct MAP_KEYDATA
{
    QString Original_Key;
    QStringList Mapping_Keys;
    bool Burst;
    bool Lock;
    bool LockStatus;

    MAP_KEYDATA() : Original_Key(), Mapping_Keys(), Burst(false), Lock(false), LockStatus(false) {}

    MAP_KEYDATA(QString originalkey, QString mappingkeys, bool burst, bool lock)
    {
        Original_Key = originalkey;
        Mapping_Keys = mappingkeys.split(SEPARATOR_STR);
        Burst = burst;
        Lock = lock;
        LockStatus = false;
    }

    bool operator==(const MAP_KEYDATA& other) const
    {
        return ((Original_Key == other.Original_Key)
                && (Mapping_Keys == other.Mapping_Keys)
                && (Burst == other.Burst)
                && (Lock == other.Lock));
    }
}MAP_KEYDATA_st;

typedef struct V_KEYCODE
{
    quint8 KeyCode;
    bool ExtenedFlag;

    V_KEYCODE() : KeyCode(0x00), ExtenedFlag(false) {}

    V_KEYCODE(quint8 keycode, bool extenedflag)
    {
        KeyCode = keycode;
        ExtenedFlag = extenedflag;
    }

    bool operator==(const V_KEYCODE& other) const
    {
        return ((KeyCode == other.KeyCode)
                && (ExtenedFlag == other.ExtenedFlag));
    }
}V_KEYCODE_st;

typedef struct V_MOUSECODE
{
    DWORD MouseDownCode;
    DWORD MouseUpCode;

    V_MOUSECODE() : MouseDownCode(0x0000), MouseUpCode(0x0000) {}

    V_MOUSECODE(DWORD mousedowncode, DWORD mouseupcode)
    {
        MouseDownCode = mousedowncode;
        MouseUpCode = mouseupcode;
    }

    bool operator==(const V_MOUSECODE& other) const
    {
        return ((MouseDownCode == other.MouseDownCode)
                && (MouseUpCode == other.MouseUpCode));
    }
}V_MOUSECODE_st;

class StyledDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    StyledDelegate(QWidget *parent = Q_NULLPTR) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class KeyListComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit KeyListComboBox(QWidget *parent = Q_NULLPTR) : QComboBox(parent)
    {
        if (parent != Q_NULLPTR){
            m_KeyMapper_ptr = parent;
        }
    }

protected:
    void keyPressEvent(QKeyEvent *keyevent);

private:
    QWidget *m_KeyMapper_ptr;
};

class QKeyMapper : public QDialog
{
    Q_OBJECT

public:
    explicit QKeyMapper(QWidget *parent = Q_NULLPTR);
    ~QKeyMapper();

    #define EXTENED_FLAG_TRUE   true
    #define EXTENED_FLAG_FALSE  false

    #define QT_KEY_EXTENDED         (0x01000000U)
    #define QT_KEY_L_SHIFT          (0x00000001U)
    #define QT_KEY_L_CTRL           (0x00000002U)
    #define QT_KEY_L_ALT            (0x00000004U)
    #define QT_KEY_L_WIN            (0x00000008U)
    #define QT_KEY_R_SHIFT          (0x00000010U)
    #define QT_KEY_R_CTRL           (0x00000020U)
    #define QT_KEY_R_ALT            (0x00000040U)
    #define QT_KEY_R_WIN            (0x00000080U)

    enum KeyMapStatus
    {
        KEYMAP_IDLE = 0U,
        KEYMAP_CHECKING,
        KEYMAP_MAPPING
    };
    Q_ENUM(KeyMapStatus)

    enum VirtualKeyCode
    {
        VK_0     = 0x30,
        VK_1,   // 0x31
        VK_2,   // 0x32
        VK_3,   // 0x33
        VK_4,   // 0x34
        VK_5,   // 0x35
        VK_6,   // 0x36
        VK_7,   // 0x37
        VK_8,   // 0x38
        VK_9,   // 0x39

        VK_A     = 0x41,
        VK_B,   // 0x42
        VK_C,   // 0x43
        VK_D,   // 0x44
        VK_E,   // 0x45
        VK_F,   // 0x46
        VK_G,   // 0x47
        VK_H,   // 0x48
        VK_I,   // 0x49
        VK_J,   // 0x4A
        VK_K,   // 0x4B
        VK_L,   // 0x4C
        VK_M,   // 0x4D
        VK_N,   // 0x4E
        VK_O,   // 0x4F
        VK_P,   // 0x50
        VK_Q,   // 0x51
        VK_R,   // 0x52
        VK_S,   // 0x53
        VK_T,   // 0x54
        VK_U,   // 0x55
        VK_V,   // 0x56
        VK_W,   // 0x57
        VK_X,   // 0x58
        VK_Y,   // 0x59
        VK_Z    // 0x5A
    };
    Q_ENUM(VirtualKeyCode)

    Q_INVOKABLE void WindowStateChangedProc(void);
    Q_INVOKABLE void cycleCheckProcessProc(void);

    void setKeyHook(HWND hWnd);
    void setKeyUnHook(void);

    void setDInputKeyHook(HWND hWnd);
    void setDInputKeyUnHook(void);

    void setMapProcessInfo(const QString &filename, const QString &windowtitle, const QString &pid, const QString &filepath, const QIcon &windowicon);

#ifdef ADJUST_PRIVILEGES
    static BOOL EnableDebugPrivilege(void);
    static BOOL AdjustPrivileges(void);
#endif
    static QKeyMapper *static_Ptr(void);
    static void getProcessInfoFromPID(DWORD processID, QString &processPathStr);
    static void getProcessInfoFromHWND(HWND hWnd, QString &processPathStr);
    static HWND getHWND_byPID(DWORD dwProcessID);
    static BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);
    static BOOL CALLBACK EnumChildWindowsProc(HWND hWnd, LPARAM lParam);
    static BOOL DosPathToNtPath(LPTSTR pszDosPath, LPTSTR pszNtPath);
    static int findInKeyMappingDataList(const QString &keyname);
    static void sendBurstKeyDown(const QString &burstKey);
    static void sendBurstKeyUp(const QString &burstKey, bool stop);
    static void sendSpecialVirtualKeyDown(const QString &virtualKey);
    static void sendSpecialVirtualKeyUp(const QString &virtualKey);

    // unused enum all process function >>>
    static void EnumProcessFunction(void);
    // unused enum all process function <<<

    bool getAutoStartMappingStatus(void);

protected:
    void changeEvent(QEvent *event);
    void timerEvent(QTimerEvent *event) override;

public slots:
    void on_keymapButton_clicked();

private slots:
    void HotKeyActivated();

    void SystrayIconActivated(QSystemTrayIcon::ActivationReason reason);

    void on_cellChanged(int row, int col);

    void on_savemaplistButton_clicked();

    void on_refreshButton_clicked();

    void on_processinfoTable_doubleClicked(const QModelIndex &index);

    void on_addmapdataButton_clicked();

    void on_deleteoneButton_clicked();

    void on_clearallButton_clicked();

    void on_moveupButton_clicked();

    void on_movedownButton_clicked();

    void on_settingselectComboBox_currentIndexChanged(int index);

private:
    static LRESULT CALLBACK LowLevelKeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK LowLevelMouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);

    static void* HookVTableFunction(void* pVTable, void* fnHookFunc, int nOffset);
    static HRESULT WINAPI hookGetDeviceState(IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData);
    static HRESULT WINAPI hookGetDeviceData(IDirectInputDevice8* pThis, DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags);

    void initHotKeySequence(void);
    void initVirtualKeyCodeMap(void);
    void initVirtualMouseButtonMap(void);
    void initProcessInfoTable(void);
    void refreshProcessInfoTable(void);
    void setProcessInfoTable(QList<MAP_PROCESSINFO> &processinfolist);
    void updateProcessInfoDisplay(void);

    void initKeyMappingDataTable(void);
    void initAddKeyComboBoxes(void);
    void refreshKeyMappingDataTable(void);
    void updateLockStatusDisplay(void);
    void clearAllBurstTimersAndLockKeys(void);

    void saveKeyMapSetting(void);
    bool loadKeyMapSetting(int settingIndex);
    bool checkMappingkeyStr(const QString &mappingkeystr);

    void loadFontFile(const QString fontfilename, int &returnback_fontid, QString &fontname);
    void setControlCustomFont(const QString &fontname);

    void changeControlEnableStatus(bool status);

    void startBurstTimer(QString burstKey, int mappingIndex);
    void stopBurstTimer(QString burstKey, int mappingIndex);

public:
    static QList<MAP_PROCESSINFO> static_ProcessInfoList;
    static QHash<QString, V_KEYCODE> VirtualKeyCodeMap;
    static QHash<QString, V_MOUSECODE> VirtualMouseButtonMap;
    static QHash<WPARAM, QString> MouseButtonNameMap;
    static QList<MAP_KEYDATA> KeyMappingDataList;
    static QStringList pressedRealKeysList;
    static QStringList pressedVirtualKeysList;
    static QStringList pressedLockKeysList;
    static GetDeviceStateT FuncPtrGetDeviceState;
    static GetDeviceDataT FuncPtrGetDeviceData;

    static QComboBox *orikeyComboBox_static;
    static QComboBox *mapkeyComboBox_static;
    static QCheckBox *disableWinKeyCheckBox_static;
    static QKeyMapper *selfPtr_static;

private:
    Ui::QKeyMapper *ui;
    quint8 m_KeyMapStatus;
    QTimer m_CycleCheckTimer;
    MAP_PROCESSINFO m_MapProcessInfo;
    QSystemTrayIcon *m_SysTrayIcon;
    HHOOK m_KeyHook;
#ifdef SUPPORT_MOUSE_LL_HOOK
    HHOOK m_MouseHook;
#endif
    IDirectInput8* m_DirectInput;
    int m_SAO_FontFamilyID;
    QString m_SAO_FontName;
    StyledDelegate *m_ProcessInfoTableDelegate;
    StyledDelegate *m_KeyMappingDataTableDelegate;
    KeyListComboBox *m_orikeyComboBox;
    KeyListComboBox *m_mapkeyComboBox;
    QHotkey *m_HotKey;
    QHash<QString, int> m_BurstTimerMap;
    QHash<QString, int> m_BurstKeyUpTimerMap;
};

#endif // QKEYMAPPER_H
