uint64_t UserInfoSimple::inputSlotTime()
{
	static tstring deftext = _T("00:30");
	
	LineDlg dlg;
	dlg.description = TSTRING(EXTRA_SLOT_TIME_FORMAT);
	dlg.title = TSTRING(EXTRA_SLOT_TIMEOUT);
	dlg.line = deftext;
	
	if (dlg.DoModal() == IDOK)
	{
		deftext = dlg.line;
		unsigned int n = 0;
		for (size_t i = 0; i < deftext.length(); i++) // TODO: cleanup.
		{
			if (deftext[i] == L':') n++;
		}
		unsigned int d, h, m;
		switch (n)
		{
			case 1:
				if (swscanf(deftext.c_str(), L"%u:%u", &h, &m) == 2)
					return (h * 3600 + m * 60);
					
				break;
			case 2:
				if (swscanf(deftext.c_str(), L"%u:%u:%u", &d, &h, &m) == 3)
					return (d * 3600 * 24 + h * 3600 + m * 60);
					
				break;
		}
		::MessageBox(GetForegroundWindow(), CTSTRING(INVALID_TIME_FORMAT), CTSTRING(ERRORS), MB_OK | MB_ICONERROR);
	}
	return 0;
}