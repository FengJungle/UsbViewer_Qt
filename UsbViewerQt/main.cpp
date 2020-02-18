#include "UsbViewerQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	UsbViewerQt w;
	w.show();
	return a.exec();
}
