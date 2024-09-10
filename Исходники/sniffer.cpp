QVariant Sniffer::getField(uint32 index)
{
	switch(index)
	{
		case 0:
			return (isDead) ? QPixmap(":/Common/no.png") : QPixmap(":/Common/ok.png");
		case 1:
			return getPid();
		case 2:
			return _packetList->rowCount();
		case 3:
			return _processName;
	}
	return QVariant();
}