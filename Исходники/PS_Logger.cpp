	void EventLogger::add(const char* lpStrDesc, EVENTTYPE t, 
		const char* lpStrSource, int value)
	{
		if(lpStrDesc == NULL)
			return;

		DAnsiStr strEvent;			
		//Write Event Type
		if(m_bWriteEventTypes)
		{
			if(t == etInfo)
				strEvent += printToAStr("INFO: ");
			else if(t == etWarning)
				strEvent += printToAStr("WARNING: ");
			else if(t == etError)
				strEvent += printToAStr("ERROR: ");
		}

		//Write Event Time
		if(m_bWriteTimeStamps)
		{
			time_t rawtime;
			time (&rawtime);
#ifdef PS_SECURE_API
			char buffer[64];
			struct tm timeinfo;
			localtime_s(&timeinfo, &rawtime);
			asctime_s(timeinfo, buffer, 64)
				strEvent += printToAStr("TIME: [%s], ", buffer);
#else
			struct tm * timeinfo = localtime ( &rawtime );
			DAnsiStr strTime = DAnsiStr(asctime(timeinfo));
			strTime.trim();
			strEvent += printToAStr("TIME: [%s], ", strTime.cptr());
#endif
		}

		//Write Source + Value
		if(m_bWriteSourceInfo && lpStrSource)
		{
			strEvent += printToAStr("SOURCE: [%s, LINE:%d], ", lpStrSource, value);
		}

		//Write Event itself
		strEvent += DAnsiStr(lpStrDesc);			
		m_lstLog.push_back(strEvent);

		//Write Message to screen
		if(m_bWriteToScreen)
			display(strEvent.cptr());

		//Update Buffer size and Flush if ready
		m_szBufferSize += strEvent.length();
		if(m_szBufferSize > PS_LOG_BUFFER_SIZE)
			flush();
	}