int checkDeviceID(uint8_t *data) {
	return (getUInt16(data) == selfProgram.getDeviceID());
}