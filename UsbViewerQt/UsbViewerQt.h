#ifndef USBVIEWERQT_H
#define USBVIEWERQT_H

#include <QtWidgets/QMainWindow>
#include "ui_UsbViewerQt.h"
#include "UsbInterface.h"
#include "log.h"

#include <QStandardItemModel>
#include <qtimer.h>

class UsbViewerQt : public QMainWindow
{
	Q_OBJECT

public:
	UsbViewerQt(QWidget *parent = 0);
	~UsbViewerQt();

	// Init treeModel
	void initTreeModel();

	// Refresh the device list
	void refreshDeviceList(DeviceClass deviceClass, QStandardItem* deviceTreeRoot);

	// Retrieve the host name
	QString getHostName();

	// timer
	QTimer* timer;

public slots:

	// slots: when the tree is clicked
	void getTreeClicked(const QModelIndex index);

	// slots: refresh tree when timer timeout
	void refreshTree();

private:
	Ui::UsbViewerQtClass ui;

	QTreeView* pTreeView;

	// UI tree root model
	QStandardItemModel* rootModel;

	// Usb device info list 
	QStringList usbInfoList;

	// System device info list 
	QStringList systemInfoList;

	// Mouse device info list
	QStringList mouseInfoList;

	// Net device info list
	QStringList netInfoList;

	// Keyboard device info list
	QStringList keyBoardInfoList;

	// Logger
	LOG* Log;
};

#endif // USBVIEWERQT_H
