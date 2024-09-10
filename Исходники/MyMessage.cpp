char* MyMessage::getString(char *buffer) const {
	uint8_t payloadType = miGetPayloadType();
	if (payloadType == P_STRING) {
		strncpy(buffer, data, miGetLength());
		buffer[miGetLength()] = 0;
		return buffer;
	} else if (buffer != NULL) {
		if (payloadType == P_BYTE) {
			itoa(bValue, buffer, 10);
		} else if (payloadType == P_INT16) {
			itoa(iValue, buffer, 10);
		} else if (payloadType == P_UINT16) {
			utoa(uiValue, buffer, 10);
		} else if (payloadType == P_LONG32) {
			ltoa(lValue, buffer, 10);
		} else if (payloadType == P_ULONG32) {
			ultoa(ulValue, buffer, 10);
		} else if (payloadType == P_FLOAT32) {
			dtostrf(fValue,2,fPrecision,buffer);
		} else if (payloadType == P_CUSTOM) {
			return getCustomString(buffer);
		}
		return buffer;
	} else {
		return NULL;
	}
}