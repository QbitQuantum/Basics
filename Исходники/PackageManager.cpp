QString PackageManager::sendLine(QDataStream &stream, QLine line, QPen pen, QString old)
{
	// "order:line:x1:y1:x2:y3:color:size"
	QString packet = "order:line:";
	packet += QString::number(line.x1()) + ":";
	packet += QString::number(line.y1()) + ":";
	packet += QString::number(line.x2()) + ":";
	packet += QString::number(line.y2()) + ":";
	packet += pen.color().name() += ":";
	packet += QString::number(pen.width());
	
	if (packet != old)
		stream << packet;
	return packet;
}