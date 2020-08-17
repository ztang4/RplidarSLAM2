#include "LidarDataViewWindow.h"

#include <QPainter>
#include <QtMath>

LidarDataViewWindow::LidarDataViewWindow(QWidget *parent) : QWidget(parent) {

}

void LidarDataViewWindow::setScan(rplidar_response_measurement_node_hq_t * nodes, int count) {
	this->nodes = nodes;

	this->countData = count;



	this->repaint();
}

void LidarDataViewWindow::paintEvent(QPaintEvent *event) {
	// unuse
	Q_UNUSED(event);

	QSize s = this->size();
	int offsetX = s.width() / 2;
	int offsetY = s.height() / 2;

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	// Position du Lidar
	painter.setPen(QPen(QColor(255, 0, 0), 2));
	for (int i = 1; i <= 5; i++) {
		painter.drawEllipse(offsetX - (i / 2), offsetY - (i / 2), i, i);
	}

	// Circle distance
	painter.setPen(QPen(QColor(0, 0, 255), 1));
	for (int i = 1; i <= 6; i++) {
		int r = i * 100;
		painter.drawEllipse(offsetX - (r / 2), offsetY - (r / 2), r, r);
	}

	painter.setPen(QPen(QColor(0, 0, 0), 2));
	if (countData != 0) {
		for (int pos = 0; pos < countData; ++pos) {
			if (nodes[pos].dist_mm_q2 == 0) {
				continue;
			}

			float angleDeg = (nodes[pos].angle_z_q14 * 90.f / (1 << 14));
			float distance = nodes[pos].dist_mm_q2 / 4.0f;

			// Substract 90 degrees to visualize the same axes on screen and from the physical device.
			float angleRad = qDegreesToRadians(angleDeg - 90);

			// 1 pixel equal 1 cm. The distance is in mm
			float dx = distance * qCos(angleRad) / 10;
			float dy = distance * qSin(angleRad) / 10;
			painter.setPen(QPen(QColor(0, 0, 0), 2));
			painter.drawPoint(offsetX + dx, offsetY + dy);

			printf("%s theta: %03.2f Dist: %08.2f Q: %d \n",
				(nodes[pos].quality & RPLIDAR_RESP_MEASUREMENT_SYNCBIT) ? "S " : "  ",
				angleDeg, distance,
				nodes[pos].quality >> RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT);
		}
	}
}
