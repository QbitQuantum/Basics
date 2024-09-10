INT WINAPI PowerButtonThread(void)
{
	DWORD nBtnCount = 0;

	PWRBTN_INF((_T("[PWR:INF] ++PowerButtonThread()\r\n")));

	while(!g_bExitThread)
	{
		WaitForSingleObject(g_hEventPowerBtn, INFINITE);

		if(g_bExitThread)
		{
			break;
		}

		Button_pwrbtn_disable_interrupt();			// Mask EINT
		Button_pwrbtn_clear_interrupt_pending();		// Clear Interrupt Pending

		InterruptDone(g_dwSysIntrPowerBtn);

		while(Button_pwrbtn_is_pushed())
		{
			// Wait for Button Released...
			Sleep(10);
		}

		nBtnCount++;
		PWRBTN_INF((_T("[PWR] Power Button Event [%d]\r\n"), nBtnCount));

		//PowerPolicyNotify(PPN_POWERBUTTONPRESSED,0);
		SetSystemPowerState(NULL, POWER_STATE_SUSPEND, POWER_FORCE);

		Button_pwrbtn_enable_interrupt();			// UnMask EINT
	}

	PWRBTN_INF((_T("[PWR:INF] --PowerButtonThread()\r\n")));

	return 0;
}