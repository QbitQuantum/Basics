int open_ifport (PORTPROP *pc)
{
	OSVERSIONINFO vinfo = { sizeof(OSVERSIONINFO) };
	LARGE_INTEGER val1;
	BYTE cmdspi[6];
	static const WORD PortsCom[] = { COM1ADR, COM2ADR, COM3ADR, COM4ADR };
	static const WORD PortsLpt[] = { LPT1ADR, LPT2ADR, LPT3ADR };
	char sComm[16];
	DCB dcb = { sizeof(DCB),
				9600, TRUE, FALSE, TRUE, FALSE,
				DTR_CONTROL_DISABLE, FALSE,
				TRUE, FALSE, FALSE, FALSE, FALSE,
				RTS_CONTROL_DISABLE, FALSE, 0, 0,
				10, 10,
				8, NOPARITY, ONESTOPBIT, '\x11', '\x13', '\xFF', '\xFF', 0 };
	COMMTIMEOUTS commtimeouts = { 0, 1, 100, 1, 300};


	/* Check if high resolution timer is supported */
	QueryPerformanceFrequency(&val1);
	if (val1.QuadPart == 0) {
		pc->Info1 = "Incompatible envilonment.\n";
		return 1;
	}

	PortDly = pc->Delay;		/* I/O delay for direct I/O control */
	dcb.BaudRate = pc->Baud;	/* Bit rate for SPI bridge */

	/* Open direct I/O driver if needed */
	if(GetVersionEx(&vinfo) == FALSE) {
		pc->Info1 = "Incompatible envilonment.\n";
		return 1;
	}
	if((vinfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
	    && ((pc->PortClass == TY_COMM)||(pc->PortClass == TY_LPT))) {
		if(init_driver()) {
			pc->Info1 = "I/O driver initialization failed.\n";
			return 1;
		}
	}

	/* Use COM port in direct I/O */
	if(pc->PortClass == TY_COMM) {
		if((pc->PortNum < 1)||(pc->PortNum > 4)) {
			pc->Info1 = "Invalid Port#.\n";
			return 1;
		}
		PortBase = PortsCom[pc->PortNum - 1];
		sprintf(str_info, "No COM%u(0x%X) port.\n", pc->PortNum, PortBase);
		pc->Info1 = str_info;
		if(check_comport()) {
			if(vinfo.dwPlatformId != VER_PLATFORM_WIN32_NT) return 1;
			sprintf(sComm, "\\\\.\\COM%u", pc->PortNum);
			hComm = CreateFile(sComm, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if(hComm == INVALID_HANDLE_VALUE) return 1;
			if(check_comport()) return 1;
		}

		_outp(COM_IMR, 0x00);		/* Mask interrupts */
		pc->Info1 = NULL;
		PortType = TY_COMM;
		return 0;
	}

	/* Use COM port via API */
	if(pc->PortClass == TY_VCOM) {
		sprintf(sComm, "\\\\.\\COM%u", pc->PortNum);
		hComm = CreateFile(sComm, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if(hComm == INVALID_HANDLE_VALUE) {
			sprintf(str_info, "%s could not be opened.\n", sComm);
			pc->Info1 = str_info;
			return 1;
		}
		SetCommState(hComm, &dcb);
		EscapeCommFunction(hComm, CLRRTS);
		EscapeCommFunction(hComm, CLRDTR);
		PortType = TY_VCOM;
		return 0;
	}

	/* Use SPI bridge attached on COM port */
	if(pc->PortClass == TY_BRIDGE) {
		sprintf(sComm, "\\\\.\\COM%u", pc->PortNum);
		hComm = CreateFile(sComm, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if(hComm == INVALID_HANDLE_VALUE) {
			sprintf(str_info, "%s could not be opened.\n", sComm);
			pc->Info1 = str_info;
			return 1;
		}
		dcb.fOutxCtsFlow = TRUE;
		dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;
		SetCommState(hComm, &dcb);
		SetCommTimeouts(hComm, &commtimeouts);
		EscapeCommFunction(hComm, CLRDTR);
		delay_ms(10);
		while(read_bridge(cmdspi, sizeof(cmdspi)));
		cmdspi[0] = FLAG-1;
		cmdspi[1] = FLAG; cmdspi[2] = SPI_ENABLE;	/* Enable Bridge */
		cmdspi[3] = FLAG; cmdspi[4] = SPI_SETDLY; cmdspi[5] = (BYTE)PortDly; /* Set SPI delay */
		send_bridge(cmdspi, 6);		/* Send bridge initialization commands */
		read_bridge(cmdspi, 2);		/* Check if the commands are accepted */
		if((cmdspi[0] != SPI_ENABLE) || (cmdspi[1] != SPI_SETDLY)) {
			sprintf(str_info, "No SPI bridge on the %s.\n", sComm);
			pc->Info1 = str_info;
			return 1;
		}
		PortType = TY_BRIDGE;
		return 0;
	}

	/* Use LPT port in direct I/O */
	if(pc->PortClass == TY_LPT) {
		if((pc->PortNum < 1)||(pc->PortNum > 3)) {
			pc->Info1 = "Invalid Port#.\n";
			return 1;
		}
		PortBase = PortsLpt[pc->PortNum - 1];
		if(check_lptport()) {
			sprintf(str_info, "No LPT%u(0x%X) port.\n", pc->PortNum, PortBase);
			pc->Info1 = str_info;
			return 1;
		}

		_outp(LPT_DAT, 0x20);	/* Check if the adapter is ByteBlasterMV (D5-ACK) */
		if(_inp(LPT_STA) & S_ACK) {
			_outp(LPT_DAT, 0);
			if((_inp(LPT_STA) & S_ACK) == 0) {
				_outp(LPT_CTL, BA_ENA);
				pc->Info1 = "Altera ByteBlasterMV was found.\n";
				PortType = TY_ALTERA;
				if(_inp(LPT_STA) & S_ERR) return 0;	/* Check target power */
				pc->Info2 = "But target power is OFF.\n";
				return 1;
			}
		}
		_outp(LPT_DAT, 0x80);	/* Check if the adapter is AVRSP (D7-PE) */
		if(_inp(LPT_STA) & S_PE) {
			_outp(LPT_DAT, 0);
			if((_inp(LPT_STA) & S_PE) == 0) {
				_outp(LPT_DAT, B_ENA);
				pc->Info1 = "AVRSP adapter was found.\n";
				PortType = TY_AVRSP;
				if(_inp(LPT_STA) & S_ERR) return 0;	/* Check target power */
				pc->Info2 = "But target power is OFF.\n";
				return 1;
			}
		}
		_outp(LPT_DAT, 0x40);	/* Check if the adapter is Xilinx JTAG (D6-BUSY-PE) */
		if((_inp(LPT_STA) & (S_PE | S_BUSY)) == S_PE) {
			_outp(LPT_DAT, 0);
			if((_inp(LPT_STA) & (S_PE | S_BUSY)) == S_BUSY) {
				pc->Info1 = "Xilinx JTAG adapter was found.\n";
				PortType = TY_XILINX;
				if(_inp(LPT_STA) & S_ERR) return 0;	/* Check target power */
				pc->Info2 = "But target power is OFF.\n";
				return 1;
			}
		}
		_outp(LPT_DAT, 0x40);	/* Check if the adapter is Lattice ISP (D6-PE) */
		if(_inp(LPT_STA) & S_PE) {
			_outp(LPT_DAT, 0);
			if((_inp(LPT_STA) & S_PE) == 0) {
				pc->Info1 = "Lattice ISP adapter was found.\n";
				PortType = TY_LATTICE;
				if(_inp(LPT_STA) & S_ERR) return 0;	/* Check target power */
				pc->Info2 = "But target power is OFF.\n";
				return 1;
			}
		}
		_outp(LPT_DAT, 0x01);	/* Check if the adapter is STK200 dongle (D0-PE) */
		if(_inp(LPT_STA) & S_PE) {
			_outp(LPT_DAT, 0);
			if((_inp(LPT_STA) & S_PE) == 0) {
				pc->Info1 = "STK200 ISP dongle was found.\n";
				PortType = TY_STK200;
				if(_inp(LPT_STA) & S_ERR) return 0;	/* Check target power */
				pc->Info2 = "But target power is OFF.\n";
				return 1;
			}
		}
		sprintf(str_info, "No ISP adapter on the LPT%u.\n", pc->PortNum);
		pc->Info1 = str_info;
		return 1;
	}

	pc->Info1 = "Invalid port class.\n";
	return 1;
}