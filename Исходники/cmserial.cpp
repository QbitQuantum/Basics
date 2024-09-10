COMMNG cmserial_create(UINT port, UINT8 param, UINT32 speed) {

	TCHAR	commstr[16];
	HANDLE	hdl;
	DCB		dcb;
	UINT	i;
	COMMNG	ret;
	CMSER	serial;

	wsprintf(commstr, _T("COM%u"), port);
	hdl = CreateFile(commstr, GENERIC_READ | GENERIC_WRITE,
												0, 0, OPEN_EXISTING, 0, NULL);
	if (hdl == INVALID_HANDLE_VALUE) {
		goto cscre_err1;
	}
	GetCommState(hdl, &dcb);
	for (i=0; i<NELEMENTS(cmserial_speed); i++) {
		if (cmserial_speed[i] >= speed) {
			dcb.BaudRate = cmserial_speed[i];
			break;
		}
	}
	dcb.ByteSize = (UINT8)(((param >> 2) & 3) + 5);
	switch(param & 0x30) {
		case 0x10:
			dcb.Parity = ODDPARITY;
			break;

		case 0x30:
			dcb.Parity = EVENPARITY;
			break;

		default:
			dcb.Parity = NOPARITY;
			break;
	}
	switch(param & 0xc0) {
		case 0x80:
			dcb.StopBits = ONE5STOPBITS;
			break;

		case 0xc0:
			dcb.StopBits = TWOSTOPBITS;
			break;

		default:
			dcb.StopBits = ONESTOPBIT;
			break;
	}
	SetCommState(hdl, &dcb);
	ret = (COMMNG)_MALLOC(sizeof(_COMMNG) + sizeof(_CMSER), "SERIAL");
	if (ret == NULL) {
		goto cscre_err2;
	}
	ret->connect = COMCONNECT_MIDI;
	ret->read = serialread;
	ret->write = serialwrite;
	ret->getstat = serialgetstat;
	ret->msg = serialmsg;
	ret->release = serialrelease;
	serial = (CMSER)(ret + 1);
	serial->hdl = hdl;
	return(ret);

cscre_err2:
	CloseHandle(hdl);

cscre_err1:
	return(NULL);
}