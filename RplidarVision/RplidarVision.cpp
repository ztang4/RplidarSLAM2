#include "RplidarVision.h"

RplidarVision::RplidarVision(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	

}
void RplidarVision::connectLedia() {
	drv = RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT);
	drv->connect("\\\\.\\com3", 256000);
	drv->setMotorPWM(MAX_MOTOR_PWM);
	drv->startMotor();
	drv->startScan(0, 1);
	scanThread = new ScanThread(this);
	scanThread->setDriver(drv);
	lidarView = new LidarDataViewWindow();
	connect(scanThread, SIGNAL(dataGrabed(rplidar_response_measurement_node_hq_t *, int)), lidarView, SLOT(setScan(rplidar_response_measurement_node_hq_t *, int)));
	scanThread->start();
	lidarView->show();

}