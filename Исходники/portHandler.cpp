qreal PortHandler::nearestPointOfLinePort(int linePortNumber, QPointF const &location) const
{
	qreal nearestPointOfLinePort = 0;
	QLineF linePort = transformPortForNodeSize(mLinePorts[linePortNumber]);
	qreal const y1 = linePort.y1();
	qreal const y2 = linePort.y2();
	qreal const x1 = linePort.x1();
	qreal const x2 = linePort.x2();

	if (x1 == x2) {
		nearestPointOfLinePort = (location.y() - y1) / (y2 - y1);
	} else if (y1 == y2) {
		nearestPointOfLinePort = (location.x() - x1) / (x2 - x1);
	} else {
		qreal const k = (y2 - y1) / (x2 - x1);
		qreal const b2 = location.y() + 1 / k * location.x();
		qreal const b = y1 - k * x1;
		qreal const x3 = k / (1 + k * k) * (b2 - b);
		nearestPointOfLinePort = (x3 - x1) / (x2 - x1);
	}
	return nearestPointOfLinePort;
}