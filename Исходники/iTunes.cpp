	bool initIT()
	{
		try
		{
			if (!FindWindowW(L"iTunes", NULL))
			{
				// AfxMessageBox(L"iTunes not running");
				
				if (initialized) app.ReleaseDispatch();

				initialized = false;
				return false;
			}
		}
		catch(COleException * e) // in case we couldn't properly release the dispatch
		{
			return false;
		}

		if (!initialized)
		{
			COleException e;
			if(!app.CreateDispatch(L"iTunes.Application", &e)) {
			   /*CString str;
			   str.Format(L"CreateDispatch() failed w/err 0x%08lx", e.m_sc);
			   AfxMessageBox(str, MB_SETFOREGROUND);*/
			   return false;
			}
			initialized = true;
		}

		return true;
	}