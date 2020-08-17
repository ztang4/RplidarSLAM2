#include "RplidarVision.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RplidarVision w;
	w.show();
	return a.exec();
}
