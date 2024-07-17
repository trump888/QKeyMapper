#ifndef QKEYMAPPER_H
#define QKEYMAPPER_H

#include <QDialog>
#include <QDebug>
#include <QMetaEnum>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QScreen>
#include <QTimer>
#include <QTimerEvent>
#include <QThread>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QHash>
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
#include <QtWin>
#endif
#include <QOperatingSystemVersion>
#include <QStyleFactory>
#include <QFontDatabase>
#include <QStyledItemDelegate>
#include <QMenu>
#include <QTableWidget>
#include <QPropertyAnimation>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QKeyEvent>
#include <QKeySequenceEdit>
#include <QStandardItemModel>
#include <QValidator>
#include <QDir>
#include <QProcess>
#include <cmath>
#include <windows.h>
#include <process.h>
#include <tlhelp32.h>
#include <Psapi.h>
#include <tchar.h>
#include <string.h>
#include <dwmapi.h>
#include <Shlobj.h>
#include <powrprof.h>
#include <setupapi.h>
#include <interception.h>
#include <libusb.h>
//#include <QKeyEvent>
//#include <QProcess>
//#include <QTextCodec>

#include "qkeymapper_worker.h"
#include "qinputdevicelistwindow.h"
#include "qitemsetupdialog.h"

extern void updateQtDisplayEnvironment(void);

struct InputDeviceInfo
{
    QString hardwareid;
    QString devicedesc;
    ushort vendorid;
    ushort productid;
    QString VendorStr;
    QString ManufacturerStr;
    QString ProductStr;
};

struct InputDevice
{
    InterceptionDevice device;
    InputDeviceInfo deviceinfo;
    QAtomicBool disabled;
};

struct USBDeviceInfo {
    QString vendorName;
    QString productName;
};

#include "interception_worker.h"

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

struct MousePoint_Info
{
    QString ori_key;
    QString map_key;
    int x;
    int y;

    MousePoint_Info() : ori_key(), map_key(), x(-1), y(-1) {}

#ifdef DEBUG_LOGOUT_ON
    friend QDebug operator<<(QDebug debug, const MousePoint_Info& info)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "\nMousePoint_Info[" << "Ori:"<< info.ori_key << ", Map:" << info.map_key << ", X:" << info.x << ", Y:" << info.y << "]";
        return debug;
    }
#endif
};

struct ValidationResult
{
    bool isValid;
    QString errorMessage;
};

class KeyMappingDataTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit KeyMappingDataTableWidget(QWidget *parent = Q_NULLPTR)
        : QTableWidget(parent), m_DraggedRow(-1) {}

    void startDrag(Qt::DropActions supportedActions) override;
    void dropEvent(QDropEvent *event) override;

private:
    int m_DraggedRow;
};

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
    void keyPressEvent(QKeyEvent *keyevent) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QWidget *m_KeyMapper_ptr;
};

class QPopupNotification : public QWidget
{
    Q_OBJECT

public:
    explicit QPopupNotification(QWidget *parent = Q_NULLPTR);

public slots:
    void showPopupNotification(const QString &message, const QString &color, int displayTime, int position);

    void hideNotification();

private:
    QLabel *m_Label;
    QTimer m_Timer;
    QPropertyAnimation *m_StartAnimation;
    QPropertyAnimation *m_StopAnimation;
    int m_DisplayTime;
};

#if 0
class KeySequenceEditOnlyOne : public QKeySequenceEdit
{
    Q_OBJECT

public:
    explicit KeySequenceEditOnlyOne(QWidget *parent = Q_NULLPTR) :
        QKeySequenceEdit(parent),
        m_DefaultKeySequence(),
        m_LastKeySequence()
    {
    }

    void setDefaultKeySequence(const QString &keysequencestr);
    QString defaultKeySequence();
    void setLastKeySequence(const QString &keysequencestr);
    QString lastKeySequence();

signals:
    void keySeqEditChanged_Signal(const QKeySequence &keysequence);

protected:
    virtual void keyPressEvent(QKeyEvent* pEvent);

private:
    QString m_DefaultKeySequence;
    QString m_LastKeySequence;
};
#endif

class QKeyMapper : public QDialog
{
    Q_OBJECT

public:
    explicit QKeyMapper(QWidget *parent = Q_NULLPTR);
    ~QKeyMapper();

    static QKeyMapper *getInstance()
    {
        return m_instance;
    }

    #define QT_KEY_EXTENDED         (0x01000000U)
    #define QT_KEY_L_SHIFT          (0x00000001U)
    #define QT_KEY_L_CTRL           (0x00000002U)
    #define QT_KEY_L_ALT            (0x00000004U)
    #define QT_KEY_L_WIN            (0x00000008U)
    #define QT_KEY_R_SHIFT          (0x00000010U)
    #define QT_KEY_R_CTRL           (0x00000020U)
    #define QT_KEY_R_ALT            (0x00000040U)
    #define QT_KEY_R_WIN            (0x00000080U)

    // Colors for 50% opacity
    #define MOUSE_L_COLOR           RGB(255, 0, 0)      /* Red */
    #define MOUSE_R_COLOR           RGB(0, 255, 0)      /* Green */
    #define MOUSE_M_COLOR           RGB(255, 255, 0)    /* Yellow */
    #define MOUSE_X1_COLOR          RGB(0, 0, 255)      /* Blue */
    #define MOUSE_X2_COLOR          RGB(255, 0, 255)    /* Purple */
    // #define MOUSE_L_COLOR           RGB(232, 131, 124)
    // #define MOUSE_R_COLOR           RGB(90, 165, 250)
    // #define MOUSE_M_COLOR           RGB(124, 205, 76)
    // #define MOUSE_X1_COLOR          RGB(239, 199, 75)
    // #define MOUSE_X2_COLOR          RGB(153, 138, 249)

    enum KeyMapStatus
    {
        KEYMAP_IDLE = 0U,
        KEYMAP_CHECKING,
        KEYMAP_MAPPING_GLOBAL,
        KEYMAP_MAPPING_MATCHED
    };
    Q_ENUM(KeyMapStatus)

    enum MappingStartMode
    {
        MAPPINGSTART_BUTTONCLICK = 0U,
        MAPPINGSTART_HOTKEY,
        MAPPINGSTART_LOADSETTING
    };
    Q_ENUM(MappingStartMode)

public slots:
    void WindowStateChangedProc(void);
    void cycleCheckProcessProc(void);
    void cycleRefreshProcessInfoTableProc(void);
    void updateHWNDListProc(void);

public:
    void setKeyHook(HWND hWnd);
    void setKeyUnHook(void);

    void setMapProcessInfo(const QString &filename, const QString &windowtitle, const QString &pid, const QString &filepath, const QIcon &windowicon);

    QString getExeFileDescription(void);

    static void getProcessInfoFromPID(DWORD processID, QString &processPathStr);
    static void getProcessInfoFromHWND(HWND hWnd, QString &processPathStr);
    static QString getProcessNameFromPID(DWORD dwProcessId);
    static HWND getHWND_byPID(DWORD dwProcessID);
    static BOOL IsAltTabWindow(HWND hWnd);
    static BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);
    static BOOL CALLBACK EnumChildWindowsProc(HWND hWnd, LPARAM lParam);
    static BOOL DosPathToNtPath(LPTSTR pszDosPath, LPTSTR pszNtPath);
    static BOOL CALLBACK EnumWindowsBgProc(HWND hWnd, LPARAM lParam);
    static void collectWindowsHWND(const QString& WindowText, HWND hWnd);
    static int findOriKeyInKeyMappingDataList(const QString &keyname);
    static int findOriKeyInKeyMappingDataList(const QString &keyname, bool& removemultiinput);
    static int findOriKeyInKeyMappingDataList_ForAddMappingData(const QString &keyname);
    static int findOriKeyInKeyMappingDataList_ForDoublePress(const QString &keyname);
    static int findOriKeyInKeyMappingDataListGlobal(const QString &keyname);
    static int findMapKeyInKeyMappingDataList(const QString &keyname);
    static ValidationResult validateOriginalKeyString(const QString &originalkeystr, int update_rowindex);
    static ValidationResult validateSingleOriginalKey(const QString &orikey, int update_rowindex);
    static ValidationResult validateSingleKeyInOriginalCombinationKey(const QString &orikey);
    static ValidationResult validateMappingKeyString(const QString &mappingkeystr, const QStringList &mappingkeyseqlist);
    static ValidationResult validateSingleMappingKey(const QString &mapkey);

    // unused enum all process function >>>
    static void EnumProcessFunction(void);
    // unused enum all process function <<<

    static void DrawMousePoints(HWND hwnd, HDC hdc, int showMode);
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    HWND createTransparentWindow(void);
    void resizeTransparentWindow(HWND hwnd, int x, int y, int width, int height);
    void destoryTransparentWindow(HWND hwnd);
    static void clearTransparentWindow(HWND hwnd, HDC hdc);
    static QPoint getMousePointFromLabelString(QString &labelstr);

    static bool getStartupMinimizedStatus(void);
    // static bool getDisableWinKeyStatus(void);
    static int getLanguageIndex(void);
    static bool getKeyMappingDataTableItemBurstStatus(int rowindex);
    static bool getKeyMappingDataTableItemLockStatus(int rowindex);
    static QString getCurrentOriKeyText(void);
    static QString getCurrentOriCombinationKeyText(void);
    static QString getSendTextString(void);
    static void setCurrentOriCombinationKeyText(const QString &newcombinationkeytext);
    // static int getBurstPressTime(void);
    // static int getBurstReleaseTime(void);
    static int getJoystick2MouseSpeedX(void);
    static int getJoystick2MouseSpeedY(void);
    static int getvJoyXSensitivity(void);
    static int getvJoyYSensitivity(void);
    static QString getVirtualGamepadType(void);
    static bool getLockCursorStatus(void);
    static int getGlobalSettingAutoStart(void);
    static bool checkGlobalSettingAutoStart(void);
    static int getDataPortNumber(void);
    static double getBrakeThreshold(void);
    static double getAccelThreshold(void);
    static bool getSendToSameTitleWindowsStatus(void);

signals:
    void HotKeyDisplaySwitchActivated_Signal(const QString &hotkey_string);
    // void HotKeyMappingSwitchActivated_Signal(const QString &hotkey_string);
    void HotKeyMappingStart_Signal(const QString &hotkey_string);
    void HotKeyMappingStop_Signal(const QString &hotkey_string);
    void updateLockStatus_Signal(void);
    void updateMousePointLabelDisplay_Signal(const QPoint &point);
    void showMousePoints_Signal(int showpoints_trigger);
    void showCarOrdinal_Signal(qint32 car_ordinal);
#ifdef VIGEM_CLIENT_SUPPORT
    void updateViGEmBusStatus_Signal(void);
    void updateVirtualGamepadListDisplay_Signal(void);
#endif
    void updateMultiInputStatus_Signal(void);
    void updateInputDeviceSelectComboBoxes_Signal(void);
    void keyMappingTableDragDropMove_Signal(int from, int to);
    void setupDialogClosed_Signal(void);
    void showPopupMessage_Signal(const QString &message, const QString &color, int displayTime);

protected:
    // bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;
    void showEvent(QShowEvent *event) override;
    void changeEvent(QEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;

public slots:
    void on_keymapButton_clicked();

    void MappingSwitch(MappingStartMode startmode);

    void updateLockStatusDisplay(void);

    void updateMousePointLabelDisplay(const QPoint &point);

    void showMousePoints(int showpoints_trigger);

    void showPopupMessage(const QString &message, const QString &color, int displayTime);

    void showCarOrdinal(qint32 car_ordinal);

    void keyMappingTableDragDropMove(int from, int to);

    void keyMappingTableItemDoubleClicked(QTableWidgetItem *item);

    // void keyMappingTableCellDoubleClicked(int row, int column);

    void setupDialogClosed(void);

#ifdef SINGLE_APPLICATION
    void raiseQKeyMapperWindow(void);
#endif

    // void updateShortcutsMap(void);
    // void freeShortcuts(void);
    // void HotKeyForMappingActivated(const QString &keyseqstr, const Qt::KeyboardModifiers &modifiers);
    // void HotKeyForMappingReleased(const QString &keyseqstr, const Qt::KeyboardModifiers &modifiers);

    // void HotKeyActivated(const QString &keyseqstr, const Qt::KeyboardModifiers &modifiers);
    // void HotKeyStartStopActivated(const QString &keyseqstr, const Qt::KeyboardModifiers &modifiers);

    void HotKeyDisplaySwitchActivated(const QString &hotkey_string);
    void HotKeyMappingSwitchActivated(const QString &hotkey_string);
    void HotKeyMappingStart(const QString &hotkey_string);
    void HotKeyMappingStop(const QString &hotkey_string);

private slots:
    void onHotKeyLineEditEditingFinished(void);

    // void onWindowSwitchKeySequenceChanged(const QKeySequence &keysequence);
    // void onWindowSwitchKeySequenceEditingFinished();
    // void onMappingSwitchKeySequenceChanged(const QKeySequence &keysequence);
    // void onMappingSwitchKeySequenceEditingFinished();
    // void onOriginalKeySequenceChanged(const QKeySequence &keysequence);
    // void onOriginalKeySequenceEditingFinished();

    void SystrayIconActivated(QSystemTrayIcon::ActivationReason reason);

    void onTrayIconMenuShowHideAction(void);

    void cellChanged_slot(int row, int col);

#ifdef VIGEM_CLIENT_SUPPORT
    void OrikeyComboBox_currentTextChangedSlot(const QString &text);
#endif

    void on_savemaplistButton_clicked();

    void on_processinfoTable_doubleClicked(const QModelIndex &index);

    void on_addmapdataButton_clicked();

    void on_deleteoneButton_clicked();

    void on_clearallButton_clicked();

    void on_moveupButton_clicked();

    void on_movedownButton_clicked();

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    void on_settingselectComboBox_textActivated(const QString &text);
#else
    void on_settingselectComboBox_currentTextChanged(const QString &text);
#endif

    void on_removeSettingButton_clicked();

    void on_autoStartupCheckBox_stateChanged(int state);

    void on_languageComboBox_currentIndexChanged(int index);

    void on_enableVirtualJoystickCheckBox_stateChanged(int state);

    void on_installViGEmBusButton_clicked();

    // void on_uninstallViGEmBusButton_clicked();

    void on_soundEffectCheckBox_stateChanged(int state);

    void on_installInterceptionButton_clicked();

    void on_multiInputDeviceListButton_clicked();

    void on_multiInputEnableCheckBox_stateChanged(int state);

    void on_virtualGamepadNumberSpinBox_valueChanged(int number);

    void on_filterKeysCheckBox_stateChanged(int state);

    void keyMappingTabl_ItemSelectionChanged();

    void on_startupMinimizedCheckBox_stateChanged(int state);

    void on_autoStartMappingCheckBox_stateChanged(int state);

private:
    // void initHotKeySequence(void);
    void initProcessInfoTable(void);
    void initSysTrayIcon(void);
    void initPopupMessage(void);
    void updateSysTrayIconMenuText(void);
    void refreshProcessInfoTable(void);
    void setProcessInfoTable(QList<MAP_PROCESSINFO> &processinfolist);
    void updateProcessInfoDisplay(void);
    void updateSystemTrayDisplay(void);
    void switchShowHide(void);
    void showWarningPopup(const QString &message);
    void showNotificationPopup(const QString &message, const QString &color, int position);

    void initKeyMappingDataTable(void);
    void resizeKeyMappingDataTableColumnWidth(void);
    void initAddKeyComboBoxes(void);
    void initInputDeviceSelectComboBoxes(void);
    void initKeyboardSelectComboBox(void);
    void initMouseSelectComboBox(void);
    void initWindowSwitchKeyLineEdit(void);
    void initMappingSwitchKeyLineEdit(void);
    // void updateWindowSwitchKeySeq(const QKeySequence &keysequence);
    // void updateMappingSwitchKeySeq(const QKeySequence &keysequence);
    void updateWindowSwitchKeyString(const QString &keystring);
    void updateMappingStartKeyString(const QString &keystring);
    void updateMappingStopKeyString(const QString &keystring);
    // void initOriginalKeySeqEdit(void);
    void initCombinationKeyLineEdit(void);
    void refreshKeyMappingDataTable(void);
    void updateMousePointsList(void);
    void reloadUILanguage(void);
    void setUILanguage_Chinese(void);
    void setUILanguage_English(void);
    void resetFontSize(void);

    bool backupFile(const QString &originalFile, const QString &backupFile);
#ifdef SETTINGSFILE_CONVERT
    bool checkSettingsFileNeedtoConvert(void);
    void renameSettingsGroup(QSettings &settings, const QString &oldName, const QString &newName);
    void convertSettingsFile(void);
#endif
    int checkAutoStartSaveSettings(const QString &executablename, const QString &windowtitle);
    int checkSaveSettings(const QString &executablename, const QString &windowtitle);
    bool readSaveSettingData(const QString &group, const QString &key, QVariant &settingdata);
    void saveKeyMapSetting(void);
    bool loadKeyMapSetting(const QString &settingtext);
    bool checkOriginalkeyStr(const QString &originalkeystr);
    bool checkMappingkeyStr(QString &mappingkeystr);
    bool validateCombinationKey(QString &input);

    void loadFontFile(const QString fontfilename, int &returnback_fontid, QString &fontname);
#ifdef USE_SAOFONT
    void setControlCustomFont(const QString &fontname);
#endif
    void setControlFontEnglish(void);
    void setControlFontChinese(void);

    void changeControlEnableStatus(bool status);

    void extractSoundFiles();
    void playStartSound();
    void playStopSound();
    void mappingStartNotification();
    void mappingStopNotification();

    void showInputDeviceListWindow(void);
    void showItemSetupDialog(int row);
    void closeItemSetupDialog(void);

    int installInterceptionDriver(void);
    int uninstallInterceptionDriver(void);

#ifdef VIGEM_CLIENT_SUPPORT
    int installViGEmBusDriver(void);
    int uninstallViGEmBusDriver(void);
public slots:
    void updateViGEmBusStatus(void);
    void updateVirtualGamepadListDisplay(void);
    Q_INVOKABLE void reconnectViGEmClient(void);
#endif

public slots:
    void updateMultiInputStatus(void);
    void updateInputDeviceSelectComboBoxes(void);

public:
    static bool s_isDestructing;
    static int s_GlobalSettingAutoStart;
    static uint s_CycleCheckLoopCount;
    static HWND s_CurrentMappingHWND;
    static QList<MAP_PROCESSINFO> static_ProcessInfoList;
    static QList<HWND> s_hWndList;
    static QList<HWND> s_last_HWNDList;
    static QList<MAP_KEYDATA> KeyMappingDataList;
    static QList<MAP_KEYDATA> KeyMappingDataListGlobal;
    static QList<MousePoint_Info> ScreenMousePointsList;
    static QList<MousePoint_Info> WindowMousePointsList;
    // static QHash<QString, QHotkey*> ShortcutsMap;
    static QString s_WindowSwitchKeyString;
    static QString s_MappingStartKeyString;
    static QString s_MappingStopKeyString;
    static qreal s_UI_scale_value;
    int m_UI_Scale;
    KeyMapStatus m_KeyMapStatus;

private:
    static QKeyMapper *m_instance;
    static QString DEFAULT_TITLE;
    Ui::QKeyMapper *ui;
    QPoint m_LastWindowPosition;
    QTimer m_CycleCheckTimer;
    QTimer m_ProcessInfoTableRefreshTimer;
public:
    MAP_PROCESSINFO m_MapProcessInfo;
private:
    QSystemTrayIcon *m_SysTrayIcon;
    QMenu *m_SysTrayIconMenu;
    QAction *m_TrayIconMenu_ShowHideAction;
    QAction *m_TrayIconMenu_QuitAction;
    QLabel* m_PopupMessageLabel;
    QPropertyAnimation* m_PopupMessageAnimation;
    QTimer m_PopupMessageTimer;
#ifdef USE_SAOFONT
    int m_SAO_FontFamilyID;
    QString m_SAO_FontName;
#endif
    KeyMappingDataTableWidget *m_KeyMappingDataTable;
    StyledDelegate *m_ProcessInfoTableDelegate;
    // StyledDelegate *m_KeyMappingDataTableDelegate;
public:
    KeyListComboBox *m_orikeyComboBox;
    KeyListComboBox *m_mapkeyComboBox;
private:
    // KeySequenceEditOnlyOne *m_windowswitchKeySeqEdit;
    // KeySequenceEditOnlyOne *m_mappingswitchKeySeqEdit;
    // KeySequenceEditOnlyOne *m_originalKeySeqEdit;
    // QHotkey *m_HotKey_ShowHide;
    // QHotkey *m_HotKey_StartStop;
    bool loadSetting_flag;
    HWND m_TransParentHandle;
    int m_TransParentWindowInitialX;
    int m_TransParentWindowInitialY;
    int m_TransParentWindowInitialWidth;
    int m_TransParentWindowInitialHeight;
    QInputDeviceListWindow *m_deviceListWindow;
    QItemSetupDialog *m_ItemSetupDialog;
    QPopupNotification *m_PopupNotification;
};
#endif // QKEYMAPPER_H
