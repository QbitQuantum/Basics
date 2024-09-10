int CNewCardThread::DoInit()
{
	int ret = -1;
	BYTE ucCardNo[5] = "";
	BYTE max_cardno[5] = {0xFE, 0xFF, 0xFF, 0xFF, 0x00};
	char stuemp_no[21] = ""; 
	SMT_SleepCard();
	// ¶ÁÈ¡ÊÚÈ¨¿¨
	ret = ReadSerial(ucCardNo);
	if (ret < 0)
	{
		Sleep(1000);
		return 0;
	}
		
	if (_mbsncmp(ucCardNo, max_cardno, sizeof(ucCardNo) - 1) == 0)
	{
		Sleep(1000);
		return 0;
	}

	((CReadCardInfoDlg*)m_pMainWnd)->SimulateKeyPress(ucCardNo);

	Sleep(1000);
	return 0;
}