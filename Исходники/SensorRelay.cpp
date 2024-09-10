void sendTime()
{
	char buffer[20];
	strcpy(buffer, "TI:");
	DateTime::GetTime(buffer + strlen(buffer), 20 - strlen(buffer), true, false);
	strcat(buffer, "\n");
	if (!xBeePort.empty())
	{
		tx16 = Tx16Request(destXbeeID, (uint8_t *)buffer, strlen(buffer));
		xbee.send(tx16);
	}

	if (!serialPort.empty())
	{
		gmBuffSerial->WriteData((uint8_t *)buffer, strlen(buffer));
	}
}