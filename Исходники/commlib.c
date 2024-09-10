void CommSendBreak(PComVar cv, int msec)
/* for only serial ports */
{
	MSG DummyMsg;

	if ( ! cv->Ready ) {
		return;
	}

	switch (cv->PortType) {
		case IdSerial:
			/* Set com port into a break state */
			SetCommBreak(cv->ComID);

			/* pause for 1 sec */
			if (SetTimer(cv->HWin, IdBreakTimer, msec, NULL) != 0) {
				GetMessage(&DummyMsg,cv->HWin,WM_TIMER,WM_TIMER);
			}

			/* Set com port into the nonbreak state */
			ClearCommBreak(cv->ComID);
			break;
	}
}