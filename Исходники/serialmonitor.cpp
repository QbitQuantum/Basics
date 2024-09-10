void SerialMonitor::ReOpenPort(void)
{
	bool go = true;
	if (serialPort.isOpen()) {
		go = ClosePort();
	}

	if (go) {
		 //connect (&serialPort, SIGNAL(readyRead()), this, SLOT(ReadSerialPort()));
         OpenPort();
	}
}