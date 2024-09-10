		/*
		@brief Logs off the current user from the active session. It is irelevant, if it is a console or rdp session.
		It needs the session number, which can be queried with the QueryActiveSession method.
		@param SessioNumber The session number to the current active session.
		@return
		*/
		bool WinApiHelper::LogOff(quint64 SessioNumber)
		{
			if (!WTSLogoffSession(WTS_CURRENT_SERVER_HANDLE, SessioNumber, true))
			{
				DWORD err = GetLastError();
				m_logger->error("WTSLogoffSession failed. GetLastError: ") << err;
				return false;
			}
			else
			{
				//This will be logged by the service. No logging needed here.
				return true;
			}
		}