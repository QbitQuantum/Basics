INT WINAPI PowerButtonThread(void)
{
	DWORD nBtnCount = 0;
	WCHAR  state[1024] = {0};
	LPWSTR pState = &state[0];
	DWORD dwBufChars = (sizeof(state) / sizeof(state[0]));
	DWORD  dwStateFlags = 0;
	DWORD dwErr;

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

		dwErr = GetSystemPowerState(pState, dwBufChars, &dwStateFlags);
		if (ERROR_SUCCESS != dwErr)
		{
			RETAILMSG(1, (TEXT("PMGET!GetSystemPowerState:ERROR:%d\n"), dwErr));
		}
		else
		{
			RETAILMSG(1, (TEXT("PMGET! System Power state is '%s', flags 0x%08x\n"), state, dwStateFlags));
		}

		InterruptDone(g_dwSysIntrPowerBtn);

#ifndef    SLEEP_AGING_TEST
		while(Button_pwrbtn_is_pushed())
		{
			// Wait for Button Released...
			Sleep(10);
		}
#endif

		nBtnCount++;
		PWRBTN_INF((_T("[PWR] Power Button Event [%d]\r\n"), nBtnCount));

		//SetSystemPowerState(NULL, POWER_STATE_SUSPEND, POWER_FORCE);
		//PowerPolicyNotify(PPN_POWERBUTTONPRESSED,0);

		if ( wcscmp(state,TEXT("screenoff")) == 0 )
		{
			RETAILMSG(1,(TEXT("setsystempowerstate to ON from screen off\r\n")));
			SetSystemPowerState( NULL, POWER_STATE_ON, POWER_FORCE );
		}
		else if ( wcscmp(state,TEXT("backlightoff")) == 0 )
		{

		#ifdef WPC
			RETAILMSG(1,(TEXT("setsystempowerstate to ON from backlight off\r\n")));
			SetSystemPowerState( NULL, POWER_STATE_ON, POWER_FORCE );
		#endif
		#ifdef SMARTFON
		  	 RETAILMSG(1,(TEXT("setsystempowerstate to IDLE from backlight off\r\n")));
			SetSystemPowerState( TEXT("useridle"), POWER_STATE_IDLE, POWER_FORCE );
		#endif
		}
		else
		{
		#ifdef WPC
			//SetSystemPowerState( NULL, POWER_STATE_SUSPEND, POWER_FORCE );
			PowerPolicyNotify(PPN_POWERBUTTONPRESSED,0);
		#endif
		#ifdef SMARTFON
			RETAILMSG(1,(TEXT("setsystempowerstate to IDLE from on\r\n")));
			SetSystemPowerState( TEXT("useridle"), POWER_STATE_IDLE, POWER_FORCE );
		#endif
		}

		Button_pwrbtn_enable_interrupt();			// UnMask EINT
#ifdef    SLEEP_AGING_TEST
        Sleep(2000);
        SetEvent(g_hEventPowerBtn);
#endif
	}

	PWRBTN_INF((_T("[PWR:INF] --PowerButtonThread()\r\n")));

	return 0;
}