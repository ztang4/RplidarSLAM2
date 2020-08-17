#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RplidarVision.h"
#include "rplidar.h" //RPLIDAR standard sdk, all-in-one header
#include "ScanThread.h"
#include "LidarDataViewWindow.h"
using namespace rp::standalone::rplidar;

class RplidarVision : public QMainWindow
{
	Q_OBJECT

public:
	RplidarVision(QWidget *parent = Q_NULLPTR);
private slots:
	void connectLedia();
private:
	ScanThread *scanThread = NULL;
	LidarDataViewWindow *lidarView = NULL;
	Ui::RplidarVisionClass ui;
	RPlidarDriver * drv;
};
