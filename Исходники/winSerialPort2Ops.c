int SerialPortOpenPortNamed(char *portName, int baudRate) {
	int portNum;
	int n = strlen(portName);
	if ((n < 4) || (n > 5)) return PRIM_FAILED;
	// assume portName is: COM<num>, where <num> is or two decimal digits
	if (digitValue(portName[3]) < 0) return PRIM_FAILED;
	portNum = digitValue(portName[3]);
	if (n == 5) {
		if (digitValue(portName[4]) < 0) return PRIM_FAILED;
		portNum = (10 * portNum) + digitValue(portName[4]);
	}
	return openPort(portNum, baudRate);
}