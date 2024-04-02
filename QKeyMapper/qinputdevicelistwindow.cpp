#include "interception_worker.h"
#include "qinputdevicelistwindow.h"
#include "ui_qinputdevicelistwindow.h"

static const char *PROGRAM_NAME = "QKeyMapper";

static const char *FONTNAME_ENGLISH = "Microsoft YaHei UI";
static const char *FONTNAME_CHINESE = "NSimSun";

static const int UI_SCALE_NORMAL = 0;
static const int UI_SCALE_1K_PERCENT_100 = 1;
static const int UI_SCALE_1K_PERCENT_125 = 2;
static const int UI_SCALE_1K_PERCENT_150 = 3;
static const int UI_SCALE_2K_PERCENT_100 = 4;
static const int UI_SCALE_2K_PERCENT_125 = 5;
static const int UI_SCALE_2K_PERCENT_150 = 6;
static const int UI_SCALE_4K_PERCENT_100 = 7;
static const int UI_SCALE_4K_PERCENT_125 = 8;
static const int UI_SCALE_4K_PERCENT_150 = 9;

static const int DEVICE_TABLE_NUMBER_COLUMN         = 0;
static const int DEVICE_TABLE_DEVICEDESC_COLUMN     = 1;
static const int DEVICE_TABLE_HARDWAREID_COLUMN     = 2;
static const int DEVICE_TABLE_VENDORID_COLUMN       = 3;
static const int DEVICE_TABLE_PRODUCTID_COLUMN      = 4;
static const int DEVICE_TABLE_VENDORSTR_COLUMN      = 5;
static const int DEVICE_TABLE_PRODUCTSTR_COLUMN     = 6;
static const int DEVICE_TABLE_MANUFACTURER_COLUMN   = 7;
static const int DEVICE_TABLE_DISABLE_COLUMN        = 8;

static const int KEYBOARD_TABLE_COLUMN_COUNT    = 9;
static const int MOUSE_TABLE_COLUMN_COUNT       = 9;

static const char *DEVICELIST_WINDOWTITLE_ENGLISH = "Input Device List";

static const char *DEVICELIST_WINDOWTITLE_CHINESE = "输入设备列表";

static const char *KEYBOARDLABEL_ENGLISH    = "Keyboard";
static const char *MOUSELABEL_ENGLISH       = "Mouse";

static const char *KEYBOARDLABEL_CHINESE    = "键盘";
static const char *MOUSELABEL_CHINESE       = "鼠标";

static const char *CONFIRMBUTTON_ENGLISH    = "OK";
static const char *CANCELBUTTON_ENGLISH     = "Cancel";

static const char *CONFIRMBUTTON_CHINESE    = "确认";
static const char *CANCELBUTTON_CHINESE     = "取消";

static const char *DEVICE_TABLE_COL0_ENGLISH = "No.";
static const char *DEVICE_TABLE_COL1_ENGLISH = "Device Description";
static const char *DEVICE_TABLE_COL2_ENGLISH = "HardwareID";
static const char *DEVICE_TABLE_COL3_ENGLISH = "VendorID";
static const char *DEVICE_TABLE_COL4_ENGLISH = "ProductID";
static const char *DEVICE_TABLE_COL5_ENGLISH = "Vendor";
static const char *DEVICE_TABLE_COL6_ENGLISH = "Product";
static const char *DEVICE_TABLE_COL7_ENGLISH = "Manufacturer";
static const char *DEVICE_TABLE_COL8_ENGLISH = "Disable";

static const char *DEVICE_TABLE_COL0_CHINESE = "No.";
static const char *DEVICE_TABLE_COL1_CHINESE = "设备描述";
static const char *DEVICE_TABLE_COL2_CHINESE = "硬件ID";
static const char *DEVICE_TABLE_COL3_CHINESE = "VendorID";
static const char *DEVICE_TABLE_COL4_CHINESE = "ProductID";
static const char *DEVICE_TABLE_COL5_CHINESE = "厂商";
static const char *DEVICE_TABLE_COL6_CHINESE = "产品名";
static const char *DEVICE_TABLE_COL7_CHINESE = "制造商";
static const char *DEVICE_TABLE_COL8_CHINESE = "禁用";


QInputDeviceListWindow::QInputDeviceListWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QInputDeviceListWindow)
{
    ui->setupUi(this);

    initKeyboardDeviceTable();
    initMouseDeviceTable();

    QObject::connect(ui->keyboardDeviceTable, &QTableWidget::cellChanged, this, &QInputDeviceListWindow::onKeyboardListCellChanged);
    QObject::connect(ui->mouseDeviceTable, &QTableWidget::cellChanged, this, &QInputDeviceListWindow::onMouseListCellChanged);
}

QInputDeviceListWindow::~QInputDeviceListWindow()
{
    delete ui;
}

void QInputDeviceListWindow::setUILanguagee(int languageindex)
{
    if (LANGUAGE_ENGLISH == languageindex) {
        setWindowTitle(DEVICELIST_WINDOWTITLE_ENGLISH);

        ui->confirmButton->setText(CONFIRMBUTTON_ENGLISH);
        ui->cancelButton->setText(CANCELBUTTON_ENGLISH);

        ui->keyboardLabel->setText(KEYBOARDLABEL_ENGLISH);
        ui->mouseLabel->setText(MOUSELABEL_ENGLISH);

        ui->keyboardDeviceTable->setHorizontalHeaderLabels(QStringList() << DEVICE_TABLE_COL0_ENGLISH
                                                                         << DEVICE_TABLE_COL1_ENGLISH
                                                                         << DEVICE_TABLE_COL2_ENGLISH
                                                                         << DEVICE_TABLE_COL3_ENGLISH
                                                                         << DEVICE_TABLE_COL4_ENGLISH
                                                                         << DEVICE_TABLE_COL5_ENGLISH
                                                                         << DEVICE_TABLE_COL6_ENGLISH
                                                                         << DEVICE_TABLE_COL7_ENGLISH
                                                                         << DEVICE_TABLE_COL8_ENGLISH );

        ui->mouseDeviceTable->setHorizontalHeaderLabels(QStringList()    << DEVICE_TABLE_COL0_ENGLISH
                                                                         << DEVICE_TABLE_COL1_ENGLISH
                                                                         << DEVICE_TABLE_COL2_ENGLISH
                                                                         << DEVICE_TABLE_COL3_ENGLISH
                                                                         << DEVICE_TABLE_COL4_ENGLISH
                                                                         << DEVICE_TABLE_COL5_ENGLISH
                                                                         << DEVICE_TABLE_COL6_ENGLISH
                                                                         << DEVICE_TABLE_COL7_ENGLISH
                                                                         << DEVICE_TABLE_COL8_ENGLISH );
    }
    else {
        setWindowTitle(DEVICELIST_WINDOWTITLE_CHINESE);

        ui->confirmButton->setText(CONFIRMBUTTON_CHINESE);
        ui->cancelButton->setText(CANCELBUTTON_CHINESE);

        ui->keyboardLabel->setText(KEYBOARDLABEL_CHINESE);
        ui->mouseLabel->setText(MOUSELABEL_CHINESE);

        ui->keyboardDeviceTable->setHorizontalHeaderLabels(QStringList() << DEVICE_TABLE_COL0_CHINESE
                                                                         << DEVICE_TABLE_COL1_CHINESE
                                                                         << DEVICE_TABLE_COL2_CHINESE
                                                                         << DEVICE_TABLE_COL3_CHINESE
                                                                         << DEVICE_TABLE_COL4_CHINESE
                                                                         << DEVICE_TABLE_COL5_CHINESE
                                                                         << DEVICE_TABLE_COL6_CHINESE
                                                                         << DEVICE_TABLE_COL7_CHINESE
                                                                         << DEVICE_TABLE_COL8_CHINESE );

        ui->mouseDeviceTable->setHorizontalHeaderLabels(QStringList()    << DEVICE_TABLE_COL0_CHINESE
                                                                         << DEVICE_TABLE_COL1_CHINESE
                                                                         << DEVICE_TABLE_COL2_CHINESE
                                                                         << DEVICE_TABLE_COL3_CHINESE
                                                                         << DEVICE_TABLE_COL4_CHINESE
                                                                         << DEVICE_TABLE_COL5_CHINESE
                                                                         << DEVICE_TABLE_COL6_CHINESE
                                                                         << DEVICE_TABLE_COL7_CHINESE
                                                                         << DEVICE_TABLE_COL8_CHINESE );
    }
}

void QInputDeviceListWindow::resetFontSize()
{
    QFont customFont;
    if (LANGUAGE_ENGLISH == QKeyMapper::getLanguageIndex()) {
        customFont = QFont(FONTNAME_ENGLISH, 9);
    }
    else {
        customFont = QFont(FONTNAME_CHINESE, 9, QFont::Bold);
    }

    int scale = QKeyMapper::getInstance()->m_UI_Scale;

    if (LANGUAGE_ENGLISH == QKeyMapper::getLanguageIndex()) {
        if (UI_SCALE_4K_PERCENT_150 == scale) {
            customFont.setPointSize(11);
        }
        else {
            customFont.setPointSize(9);
        }
    }
    else {
        if (UI_SCALE_4K_PERCENT_150 == scale) {
            customFont.setPointSize(13);
        }
        else {
            customFont.setPointSize(11);
        }
    }

    ui->keyboardLabel->setFont(customFont);
    ui->mouseLabel->setFont(customFont);

    if (UI_SCALE_4K_PERCENT_150 == scale) {
        customFont.setPointSize(11);
    }
    else {
        customFont.setPointSize(9);
    }

    ui->confirmButton->setFont(customFont);
    ui->cancelButton->setFont(customFont);

    ui->keyboardDeviceTable->horizontalHeader()->setFont(customFont);
    ui->mouseDeviceTable->horizontalHeader()->setFont(customFont);

    ui->keyboardDeviceTable->setFont(QFont("Microsoft YaHei", 9));
    ui->mouseDeviceTable->setFont(QFont("Microsoft YaHei", 9));

    if (UI_SCALE_4K_PERCENT_150 == scale) {
        /* change hight to 265 */
        ui->keyboardDeviceTable->setFixedHeight(265);
        ui->mouseDeviceTable->setFixedHeight(265);
    }
    else {
        /* change hight to 268 */
        ui->keyboardDeviceTable->setFixedHeight(268);
        ui->mouseDeviceTable->setFixedHeight(268);
    }
}

void QInputDeviceListWindow::updateDeviceListInfo()
{
    updateKeyboardDeviceListInfo();
    updateMouseDeviceListInfo();
}

void QInputDeviceListWindow::updateKeyboardDeviceListInfo()
{
    ui->keyboardDeviceTable->clearContents();
    ui->keyboardDeviceTable->setRowCount(0);

    QList<InputDevice> keyboardlist = Interception_Worker::getKeyboardDeviceList();
    int rowindex = 0;
    ui->keyboardDeviceTable->setRowCount(keyboardlist.size());

    // Temporarily block the signal emit
    ui->keyboardDeviceTable->blockSignals(true);
    for (const InputDevice &inputdevice : keyboardlist)
    {
        QTableWidgetItem *number_TableItem = new QTableWidgetItem(QString::number(rowindex));
        ui->keyboardDeviceTable->setItem(rowindex, DEVICE_TABLE_NUMBER_COLUMN, number_TableItem);

        if (inputdevice.deviceinfo.hardwareid.isEmpty()) {
            rowindex += 1;
            continue;
        }

        QTableWidgetItem *devicedesc_TableItem = new QTableWidgetItem(inputdevice.deviceinfo.devicedesc);
        devicedesc_TableItem->setToolTip(inputdevice.deviceinfo.devicedesc);
        ui->keyboardDeviceTable->setItem(rowindex, DEVICE_TABLE_DEVICEDESC_COLUMN, devicedesc_TableItem);

        QTableWidgetItem *hardwareid_TableItem = new QTableWidgetItem(inputdevice.deviceinfo.hardwareid);
        hardwareid_TableItem->setToolTip(inputdevice.deviceinfo.hardwareid);
        ui->keyboardDeviceTable->setItem(rowindex, DEVICE_TABLE_HARDWAREID_COLUMN, hardwareid_TableItem);

        QTableWidgetItem *disableBox = new QTableWidgetItem();
        if (inputdevice.disabled == true) {
            disableBox->setCheckState(Qt::Checked);
        }
        else {
            disableBox->setCheckState(Qt::Unchecked);
        }
        ui->keyboardDeviceTable->setItem(rowindex, DEVICE_TABLE_DISABLE_COLUMN, disableBox);

        if (inputdevice.deviceinfo.vendorid == 0 && inputdevice.deviceinfo.productid == 0) {
            rowindex += 1;
            continue;
        }

        QString vendorIdStr = QString("0x%1").arg(QString::number(inputdevice.deviceinfo.vendorid, 16).toUpper(), 4, '0');
        QTableWidgetItem *vendorid_TableItem = new QTableWidgetItem(vendorIdStr);
        vendorid_TableItem->setToolTip(vendorIdStr);
        ui->keyboardDeviceTable->setItem(rowindex, DEVICE_TABLE_VENDORID_COLUMN, vendorid_TableItem);

        QString productIdStr = QString("0x%1").arg(QString::number(inputdevice.deviceinfo.productid, 16).toUpper(), 4, '0');
        QTableWidgetItem *productid_TableItem = new QTableWidgetItem(productIdStr);
        productid_TableItem->setToolTip(productIdStr);
        ui->keyboardDeviceTable->setItem(rowindex, DEVICE_TABLE_PRODUCTID_COLUMN, productid_TableItem);

        QTableWidgetItem *VendorStr_TableItem = new QTableWidgetItem(inputdevice.deviceinfo.VendorStr);
        VendorStr_TableItem->setToolTip(inputdevice.deviceinfo.VendorStr);
        ui->keyboardDeviceTable->setItem(rowindex, DEVICE_TABLE_VENDORSTR_COLUMN, VendorStr_TableItem);

        QTableWidgetItem *ProductStr_TableItem = new QTableWidgetItem(inputdevice.deviceinfo.ProductStr);
        ProductStr_TableItem->setToolTip(inputdevice.deviceinfo.ProductStr);
        ui->keyboardDeviceTable->setItem(rowindex, DEVICE_TABLE_PRODUCTSTR_COLUMN, ProductStr_TableItem);

        QTableWidgetItem *ManufacturerStr_TableItem = new QTableWidgetItem(inputdevice.deviceinfo.ManufacturerStr);
        ManufacturerStr_TableItem->setToolTip(inputdevice.deviceinfo.ProductStr);
        ui->keyboardDeviceTable->setItem(rowindex, DEVICE_TABLE_MANUFACTURER_COLUMN, ManufacturerStr_TableItem);

        rowindex += 1;
    }
    // Restore the signal emit
    ui->keyboardDeviceTable->blockSignals(false);

    InterceptionDevice lastkeyboard = Interception_Worker::lastOperateKeyboardDevice;
    if (interception_is_keyboard(lastkeyboard)) {
        int select_index = lastkeyboard - INTERCEPTION_KEYBOARD(0);
        selectKeyboardDeviceListRow(select_index);
    }
}

void QInputDeviceListWindow::updateMouseDeviceListInfo()
{
    ui->mouseDeviceTable->clearContents();
    ui->mouseDeviceTable->setRowCount(0);

    QList<InputDevice> mouselist = Interception_Worker::getMouseDeviceList();
    int rowindex = 0;
    ui->mouseDeviceTable->setRowCount(mouselist.size());

    // Temporarily block the signal emit
    ui->mouseDeviceTable->blockSignals(true);
    for (const InputDevice &inputdevice : mouselist)
    {
        QTableWidgetItem *number_TableItem = new QTableWidgetItem(QString::number(rowindex));
        ui->mouseDeviceTable->setItem(rowindex, DEVICE_TABLE_NUMBER_COLUMN, number_TableItem);

        if (inputdevice.deviceinfo.hardwareid.isEmpty()) {
            rowindex += 1;
            continue;
        }

        QTableWidgetItem *devicedesc_TableItem = new QTableWidgetItem(inputdevice.deviceinfo.devicedesc);
        devicedesc_TableItem->setToolTip(inputdevice.deviceinfo.devicedesc);
        ui->mouseDeviceTable->setItem(rowindex, DEVICE_TABLE_DEVICEDESC_COLUMN, devicedesc_TableItem);

        QTableWidgetItem *hardwareid_TableItem = new QTableWidgetItem(inputdevice.deviceinfo.hardwareid);
        hardwareid_TableItem->setToolTip(inputdevice.deviceinfo.hardwareid);
        ui->mouseDeviceTable->setItem(rowindex, DEVICE_TABLE_HARDWAREID_COLUMN, hardwareid_TableItem);

        QTableWidgetItem *disableBox = new QTableWidgetItem();
        if (inputdevice.disabled == true) {
            disableBox->setCheckState(Qt::Checked);
        }
        else {
            disableBox->setCheckState(Qt::Unchecked);
        }
        ui->mouseDeviceTable->setItem(rowindex, DEVICE_TABLE_DISABLE_COLUMN, disableBox);

        if (inputdevice.deviceinfo.vendorid == 0 && inputdevice.deviceinfo.productid == 0) {
            rowindex += 1;
            continue;
        }

        QString vendorIdStr = QString("0x%1").arg(QString::number(inputdevice.deviceinfo.vendorid, 16).toUpper(), 4, '0');
        QTableWidgetItem *vendorid_TableItem = new QTableWidgetItem(vendorIdStr);
        vendorid_TableItem->setToolTip(vendorIdStr);
        ui->mouseDeviceTable->setItem(rowindex, DEVICE_TABLE_VENDORID_COLUMN, vendorid_TableItem);

        QString productIdStr = QString("0x%1").arg(QString::number(inputdevice.deviceinfo.productid, 16).toUpper(), 4, '0');
        QTableWidgetItem *productid_TableItem = new QTableWidgetItem(productIdStr);
        productid_TableItem->setToolTip(productIdStr);
        ui->mouseDeviceTable->setItem(rowindex, DEVICE_TABLE_PRODUCTID_COLUMN, productid_TableItem);

        QTableWidgetItem *VendorStr_TableItem = new QTableWidgetItem(inputdevice.deviceinfo.VendorStr);
        VendorStr_TableItem->setToolTip(inputdevice.deviceinfo.VendorStr);
        ui->mouseDeviceTable->setItem(rowindex, DEVICE_TABLE_VENDORSTR_COLUMN, VendorStr_TableItem);

        QTableWidgetItem *ProductStr_TableItem = new QTableWidgetItem(inputdevice.deviceinfo.ProductStr);
        ProductStr_TableItem->setToolTip(inputdevice.deviceinfo.ProductStr);
        ui->mouseDeviceTable->setItem(rowindex, DEVICE_TABLE_PRODUCTSTR_COLUMN, ProductStr_TableItem);

        QTableWidgetItem *ManufacturerStr_TableItem = new QTableWidgetItem(inputdevice.deviceinfo.ManufacturerStr);
        ManufacturerStr_TableItem->setToolTip(inputdevice.deviceinfo.ProductStr);
        ui->mouseDeviceTable->setItem(rowindex, DEVICE_TABLE_MANUFACTURER_COLUMN, ManufacturerStr_TableItem);

        rowindex += 1;
    }
    // Restore the signal emit
    ui->mouseDeviceTable->blockSignals(false);

    InterceptionDevice lastmouse = Interception_Worker::lastOperateMouseDevice;
    if (interception_is_mouse(lastmouse)) {
        int select_index = lastmouse - INTERCEPTION_MOUSE(0);
        selectMouseDeviceListRow(select_index);
    }
}

void QInputDeviceListWindow::selectKeyboardDeviceListRow(int select_rowindex)
{
    QTableWidgetSelectionRange selection = QTableWidgetSelectionRange(select_rowindex, 0, select_rowindex, KEYBOARD_TABLE_COLUMN_COUNT - 1);
    ui->keyboardDeviceTable->setRangeSelected(selection, true);
}

void QInputDeviceListWindow::selectMouseDeviceListRow(int select_rowindex)
{
    QTableWidgetSelectionRange selection = QTableWidgetSelectionRange(select_rowindex, 0, select_rowindex, MOUSE_TABLE_COLUMN_COUNT - 1);
    ui->mouseDeviceTable->setRangeSelected(selection, true);
}

void QInputDeviceListWindow::writeDeviceList()
{
    writeKeyboardDeviceList();
    writeMouseDeviceList();
}

void QInputDeviceListWindow::writeKeyboardDeviceList()
{
    QList<InputDevice> keyboardlist = Interception_Worker::getKeyboardDeviceList();

    int rowCount = ui->keyboardDeviceTable->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        QTableWidgetItem* item = ui->keyboardDeviceTable->item(row, DEVICE_TABLE_DISABLE_COLUMN);
        if (item != Q_NULLPTR) {
            if (Qt::Checked == item->checkState()) {
                if (!keyboardlist.at(row).disabled) {
                    Interception_Worker::setInputDeviceDisabled(INTERCEPTION_KEYBOARD(row), true);
                }
            }
            else {
                if (keyboardlist.at(row).disabled) {
                    Interception_Worker::setInputDeviceDisabled(INTERCEPTION_KEYBOARD(row), false);
                }
            }
        }
    }
}

void QInputDeviceListWindow::writeMouseDeviceList()
{
    QList<InputDevice> mouselist = Interception_Worker::getMouseDeviceList();

    int rowCount = ui->mouseDeviceTable->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        QTableWidgetItem* item = ui->mouseDeviceTable->item(row, DEVICE_TABLE_DISABLE_COLUMN);
        if (item != Q_NULLPTR) {
            if (Qt::Checked == item->checkState()) {
                if (!mouselist.at(row).disabled) {
                    Interception_Worker::setInputDeviceDisabled(INTERCEPTION_MOUSE(row), true);
                }
            }
            else {
                if (mouselist.at(row).disabled) {
                    Interception_Worker::setInputDeviceDisabled(INTERCEPTION_MOUSE(row), false);
                }
            }
        }
    }
}

void QInputDeviceListWindow::showEvent(QShowEvent *event)
{
    (void)Interception_Worker::getRefreshedKeyboardDeviceList();
    (void)Interception_Worker::getRefreshedMouseDeviceList();
    updateDeviceListInfo();

    QDialog::showEvent(event);
}

void QInputDeviceListWindow::initKeyboardDeviceTable()
{
    ui->keyboardDeviceTable->setFocusPolicy(Qt::NoFocus);
    ui->keyboardDeviceTable->setColumnCount(KEYBOARD_TABLE_COLUMN_COUNT);
    ui->keyboardDeviceTable->horizontalHeader()->setStretchLastSection(true);
    ui->keyboardDeviceTable->horizontalHeader()->setHighlightSections(false);
    ui->keyboardDeviceTable->verticalHeader()->setVisible(false);
    ui->keyboardDeviceTable->verticalHeader()->setDefaultSectionSize(25);
    ui->keyboardDeviceTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->keyboardDeviceTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->keyboardDeviceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int number_width = 26;
    int devicedesc_width = ui->keyboardDeviceTable->width()/7;
    int vendorid_width = 60;
    int productid_width = 60;
    int vendorstr_width = ui->keyboardDeviceTable->width()/7 - 40;
    int productstr_width = ui->keyboardDeviceTable->width()/5 - 30;
    int manufacturer_width = vendorstr_width;
    int disable_width = 30;
    int hardwareid_width = ui->keyboardDeviceTable->width() - number_width - devicedesc_width - vendorid_width - productid_width - vendorstr_width - productstr_width - manufacturer_width - disable_width - 12;

    ui->keyboardDeviceTable->setColumnWidth(DEVICE_TABLE_NUMBER_COLUMN, number_width);
    ui->keyboardDeviceTable->setColumnWidth(DEVICE_TABLE_DEVICEDESC_COLUMN, devicedesc_width);
    ui->keyboardDeviceTable->setColumnWidth(DEVICE_TABLE_HARDWAREID_COLUMN, hardwareid_width);
    ui->keyboardDeviceTable->setColumnWidth(DEVICE_TABLE_VENDORID_COLUMN, vendorid_width);
    ui->keyboardDeviceTable->setColumnWidth(DEVICE_TABLE_PRODUCTID_COLUMN, productid_width);
    ui->keyboardDeviceTable->setColumnWidth(DEVICE_TABLE_VENDORSTR_COLUMN, vendorstr_width);
    ui->keyboardDeviceTable->setColumnWidth(DEVICE_TABLE_PRODUCTSTR_COLUMN, productstr_width);
    ui->keyboardDeviceTable->setColumnWidth(DEVICE_TABLE_MANUFACTURER_COLUMN, manufacturer_width);
    ui->keyboardDeviceTable->setColumnWidth(DEVICE_TABLE_DISABLE_COLUMN, disable_width);
}

void QInputDeviceListWindow::initMouseDeviceTable()
{
    ui->mouseDeviceTable->setFocusPolicy(Qt::NoFocus);
    ui->mouseDeviceTable->setColumnCount(MOUSE_TABLE_COLUMN_COUNT);
    ui->mouseDeviceTable->horizontalHeader()->setStretchLastSection(true);
    ui->mouseDeviceTable->horizontalHeader()->setHighlightSections(false);
    ui->mouseDeviceTable->verticalHeader()->setVisible(false);
    ui->mouseDeviceTable->verticalHeader()->setDefaultSectionSize(25);
    ui->mouseDeviceTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->mouseDeviceTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->mouseDeviceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int number_width = 26;
    int devicedesc_width = ui->mouseDeviceTable->width()/7;
    int vendorid_width = 60;
    int productid_width = 60;
    int vendorstr_width = ui->mouseDeviceTable->width()/7 - 40;
    int productstr_width = ui->mouseDeviceTable->width()/5 - 30;
    int manufacturer_width = vendorstr_width;
    int disable_width = 30;
    int hardwareid_width = ui->mouseDeviceTable->width() - number_width - devicedesc_width - vendorid_width - productid_width - vendorstr_width - productstr_width - manufacturer_width - disable_width - 12;

    ui->mouseDeviceTable->setColumnWidth(DEVICE_TABLE_NUMBER_COLUMN, number_width);
    ui->mouseDeviceTable->setColumnWidth(DEVICE_TABLE_DEVICEDESC_COLUMN, devicedesc_width);
    ui->mouseDeviceTable->setColumnWidth(DEVICE_TABLE_HARDWAREID_COLUMN, hardwareid_width);
    ui->mouseDeviceTable->setColumnWidth(DEVICE_TABLE_VENDORID_COLUMN, vendorid_width);
    ui->mouseDeviceTable->setColumnWidth(DEVICE_TABLE_PRODUCTID_COLUMN, productid_width);
    ui->mouseDeviceTable->setColumnWidth(DEVICE_TABLE_VENDORSTR_COLUMN, vendorstr_width);
    ui->mouseDeviceTable->setColumnWidth(DEVICE_TABLE_PRODUCTSTR_COLUMN, productstr_width);
    ui->mouseDeviceTable->setColumnWidth(DEVICE_TABLE_MANUFACTURER_COLUMN, manufacturer_width);
    ui->mouseDeviceTable->setColumnWidth(DEVICE_TABLE_DISABLE_COLUMN, disable_width);
}

void QInputDeviceListWindow::onKeyboardListCellChanged(int row, int col)
{
    if (col == DEVICE_TABLE_DISABLE_COLUMN) {
        bool disable = false;
        if (ui->keyboardDeviceTable->item(row, col)->checkState() == Qt::Checked) {
            disable = true;
        }
        else {
            disable = false;
        }

#ifdef DEBUG_LOGOUT_ON
        qDebug("[onKeyboardListCellChanged] row(%d) Disable = %s", row, disable == true?"ON":"OFF");
#endif

        if (disable) {
            InterceptionDevice lastkeyboard = Interception_Worker::lastOperateKeyboardDevice;

            if (lastkeyboard - INTERCEPTION_KEYBOARD(0) == row) {
                // Temporarily block the signal emit
                ui->keyboardDeviceTable->blockSignals(true);
                ui->keyboardDeviceTable->item(row, col)->setCheckState(Qt::Unchecked);
                QString message;
                if (LANGUAGE_ENGLISH == QKeyMapper::getLanguageIndex()) {
                    message = "Disabling the input device that is currently in use will prevent any further operations!";
                }
                else {
                    message = "禁用正在使用的输入设备会导致无法继续进行任何操作！";
                }

                QMessageBox::StandardButton reply;
                if (LANGUAGE_ENGLISH == QKeyMapper::getLanguageIndex()) {
                    reply = QMessageBox::warning(this, PROGRAM_NAME, message, QMessageBox::Yes | QMessageBox::No);
                }
                else {
                    reply = QMessageBox::warning(this, PROGRAM_NAME, message, QMessageBox::Yes | QMessageBox::No);
                }

                if (reply == QMessageBox::No) {
                    ui->keyboardDeviceTable->item(row, col)->setCheckState(Qt::Unchecked);
#ifdef DEBUG_LOGOUT_ON
                    qDebug() << "[onKeyboardListCellChanged]" << "User click confirm button of Disabled Warning MessageBox.";
#endif
                }
                else {
                    ui->keyboardDeviceTable->item(row, col)->setCheckState(Qt::Checked);
#ifdef DEBUG_LOGOUT_ON
                    qDebug() << "[onKeyboardListCellChanged]" << "User click cancel button of Disabled Warning MessageBox.";
#endif
                }

                // Restore the signal emit
                ui->keyboardDeviceTable->blockSignals(false);
            }
        }
    }
}

void QInputDeviceListWindow::onMouseListCellChanged(int row, int col)
{
    if (col == DEVICE_TABLE_DISABLE_COLUMN) {
        bool disable = false;
        if (ui->mouseDeviceTable->item(row, col)->checkState() == Qt::Checked) {
            disable = true;
        }
        else {
            disable = false;
        }

#ifdef DEBUG_LOGOUT_ON
        qDebug("[onMouseListCellChanged] row(%d) Disable = %s", row, disable == true?"ON":"OFF");
#endif

        if (disable) {
            InterceptionDevice lastmouse = Interception_Worker::lastOperateMouseDevice;

            if (lastmouse - INTERCEPTION_MOUSE(0) == row) {
                // Temporarily block the signal emit
                ui->mouseDeviceTable->blockSignals(true);
                ui->mouseDeviceTable->item(row, col)->setCheckState(Qt::Unchecked);
                QString message;
                if (LANGUAGE_ENGLISH == QKeyMapper::getLanguageIndex()) {
                    message = "Disabling the input device that is currently in use will prevent any further operations!";
                }
                else {
                    message = "禁用正在使用的输入设备会导致无法继续进行任何操作！";
                }

                QMessageBox::StandardButton reply;
                if (LANGUAGE_ENGLISH == QKeyMapper::getLanguageIndex()) {
                    reply = QMessageBox::warning(this, PROGRAM_NAME, message, QMessageBox::Yes | QMessageBox::No);
                }
                else {
                    reply = QMessageBox::warning(this, PROGRAM_NAME, message, QMessageBox::Yes | QMessageBox::No);
                }

                if (reply == QMessageBox::No) {
                    ui->mouseDeviceTable->item(row, col)->setCheckState(Qt::Unchecked);
#ifdef DEBUG_LOGOUT_ON
                    qDebug() << "[onMouseListCellChanged]" << "User click confirm button of Disabled Warning MessageBox.";
#endif
                }
                else {
                    ui->mouseDeviceTable->item(row, col)->setCheckState(Qt::Checked);
#ifdef DEBUG_LOGOUT_ON
                    qDebug() << "[onMouseListCellChanged]" << "User click cancel button of Disabled Warning MessageBox.";
#endif
                }

                // Restore the signal emit
                ui->mouseDeviceTable->blockSignals(false);
            }
        }
    }
}


void QInputDeviceListWindow::on_confirmButton_clicked()
{
    writeDeviceList();
    hide();
}


void QInputDeviceListWindow::on_cancelButton_clicked()
{
    hide();
}
