void LCD_UpdateThread(void * Control)
{
	CMPC_Lcd * ctrl = static_cast<CMPC_Lcd *> (Control);
	wchar_t str[40];
	__time64_t ltime;
	__time64_t otime = 0;
	struct tm  thetime;
	_tsetlocale(LC_ALL, _T(""));			// set current system locale

	while (ctrl->Thread_Loop) {
		EnterCriticalSection(&ctrl->cs);
		if (_time64(&ltime) != otime) {	// Retrieve the time
			otime = ltime;
			_localtime64_s(&thetime, &ltime);

			// Format the current time structure into a string
			// using %#x is the long date representation,
			// appropriate to the current locale
			if (wcsftime(str, sizeof(str)/sizeof(wchar_t), _T("%#x"), (const struct tm *)&thetime) &&
					(ltime > ctrl->nThread_tTimeout || ltime < otime)) {	// message displayed, no update until timeout
				ctrl->m_Manager.m_Text[0].SetText(str);
			}

			if (wcsftime(str, sizeof(str)/sizeof(wchar_t), _T("%X"), (const struct tm *)&thetime)) {
				ctrl->m_Manager.m_Text[1].SetText(str);
			}
		}

		ctrl->m_Output.Update(GetTickCount());	// This invokes OnUpdate for the active screen
		ctrl->m_Output.Draw();			// This invokes OnDraw for the active screen
		LeaveCriticalSection(&ctrl->cs);
		Sleep(LCD_UPD_TIMER);
	}

	_endthread();
}