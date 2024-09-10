BOOL XSendPacket(PFileVar fv, PXVar xv, PComVar cv)
{
	BYTE b;
	int i;
	BOOL SendFlag;
	WORD Check;

	SendFlag = FALSE;
	if (xv->PktBufCount == 0) {
		i = XRead1Byte(fv, xv, cv, &b);
		do {
			if (i == 0)
				return TRUE;
			switch (b) {
			case ACK:
				if (!fv->FileOpen) {
					fv->Success = TRUE;
					return FALSE;
				} else if (xv->PktNumSent == (BYTE) (xv->PktNum + 1)) {
					xv->PktNum = xv->PktNumSent;
					if (xv->PktNum == 0)
						xv->PktNumOffset = xv->PktNumOffset + 256;
					SendFlag = TRUE;
				}
				break;
			case NAK:
				if (xv->PktNum == 0 && xv->XOpt == Xopt1K) {
					/* we wanted 1k with CRC, but the other end specified checksum */
					/* keep the 1k block, but move back to checksum mode.          */
					xv->XOpt = XoptCheck;
					xv->CheckLen = 1;
				}
				SendFlag = TRUE;
				break;
			case CAN:
				break;
			case 0x43:
				if ((xv->PktNum == 0) && (xv->PktNumOffset == 0) && (xv->PktNumSent == 0)) {
					 if ((xv->XOpt == XoptCheck))
						XSetOpt(fv, xv, XoptCRC);
					SendFlag = TRUE;
				}
				break;
			}
			if (!SendFlag)
				i = XRead1Byte(fv, xv, cv, &b);
		} while (!SendFlag);
		// reset timeout timer
		FTSetTimeOut(fv, TimeOutVeryLong);

		do {
			i = XRead1Byte(fv, xv, cv, &b);
		} while (i != 0);

		if (xv->PktNumSent == xv->PktNum) {	/* make a new packet */
			xv->PktNumSent++;
			if (xv->DataLen == 128)
				xv->PktOut[0] = SOH;
			else
				xv->PktOut[0] = STX;
			xv->PktOut[1] = xv->PktNumSent;
			xv->PktOut[2] = ~xv->PktNumSent;

			i = 1;
			while ((i <= xv->DataLen) && fv->FileOpen &&
				   (_lread(fv->FileHandle, &b, 1) == 1)) {
				xv->PktOut[2 + i] = b;
				i++;
				fv->ByteCount++;
			}

			if (i > 1) {
				while (i <= xv->DataLen) {
					xv->PktOut[2 + i] = 0x1A;
					i++;
				}

				Check = XCalcCheck(xv, xv->PktOut);
				if (xv->CheckLen == 1)	/* Checksum */
					xv->PktOut[xv->DataLen + 3] = (BYTE) Check;
				else {
					xv->PktOut[xv->DataLen + 3] = HIBYTE(Check);
					xv->PktOut[xv->DataLen + 4] = LOBYTE(Check);
				}
				xv->PktBufCount = 3 + xv->DataLen + xv->CheckLen;
			} else {			/* send EOT */
				if (fv->FileOpen) {
					_lclose(fv->FileHandle);
					fv->FileHandle = 0;
					fv->FileOpen = FALSE;
				}
				xv->PktOut[0] = EOT;
				xv->PktBufCount = 1;
			}
		} else {				/* resend packet */
			if (xv->PktOut[0] == EOT) {
				xv->PktBufCount = 1;
			} else {
				xv->PktBufCount = 3 + xv->DataLen + xv->CheckLen;
			}
		}
		xv->PktBufPtr = 0;
	}
	/* a NAK or C could have arrived while we were buffering.  Consume it. */
	do {
		i = XRead1Byte(fv, xv, cv, &b);
	} while (i != 0);

	i = 1;
	while ((xv->PktBufCount > 0) && (i > 0)) {
		b = xv->PktOut[xv->PktBufPtr];
		i = XWrite(fv, xv, cv, &b, 1);
		if (i > 0) {
			xv->PktBufCount--;
			xv->PktBufPtr++;
		}
	}

	if (xv->PktBufCount == 0) {
		if (xv->PktNumSent == 0) {
			SetDlgNum(fv->HWin, IDC_PROTOPKTNUM, xv->PktNumOffset + 256);
		}
		else {
			SetDlgNum(fv->HWin, IDC_PROTOPKTNUM, xv->PktNumOffset + xv->PktNumSent);
		}
		SetDlgNum(fv->HWin, IDC_PROTOBYTECOUNT, fv->ByteCount);
		SetDlgPercent(fv->HWin, IDC_PROTOPERCENT, IDC_PROTOPROGRESS,
		              fv->ByteCount, fv->FileSize, &fv->ProgStat);
		SetDlgTime(fv->HWin, IDC_PROTOELAPSEDTIME, fv->StartTime, fv->ByteCount);
	}

	return TRUE;
}