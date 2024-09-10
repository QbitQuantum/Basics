void CAutoRegisterConfig::ReadFrom()
{
	CString iniFile = theApp.GetWorkPath();
	iniFile.Append(_T("\\IBAConfig\\register.ini"));

	{
		CString str;
		::GetPrivateProfileString(_T("Base"), _T("Amount24"), _T(""), str.GetBuffer(200), 200, iniFile);
		str.ReleaseBuffer();
		Set24Amount(str);
	}

	{
		m_arrayRandomAmount.clear();
		CString str;
		::GetPrivateProfileString(_T("Base"), _T("RandomAmount"), _T("5,10,20"), str.GetBuffer(200), 200, iniFile);
		str.ReleaseBuffer();
		CStringArray strArray;
		CIBAHelpper::SplitLine(str, strArray, _T(','));
		for (int i = 0; i < strArray.GetCount(); i++)
		{
			m_arrayRandomAmount.push_back(_ttoi(strArray.GetAt(i)));
		}
	}
	{
		CString str;
		::GetPrivateProfileString(_T("Base"), _T("StartTime"), _T(""), str.GetBuffer(200), 200, iniFile);
		str.ReleaseBuffer();
		str.Remove(_T(' '));
		str.Remove(_T('-'));
		str.Remove(_T(':'));
		m_startTime = CIBAHelpper::CenterTimeToOleDateTime(str);
	}
	{
		CString str;
		::GetPrivateProfileString(_T("Base"), _T("EndTime"), _T(""), str.GetBuffer(200), 200, iniFile);
		str.ReleaseBuffer();
		str.Remove(_T(' '));
		str.Remove(_T('-'));
		str.Remove(_T(':'));
		m_endTime = CIBAHelpper::CenterTimeToOleDateTime(str);
	}
	{
		CString str;
		::GetPrivateProfileString(_T("Base"), _T("IDFile"), _T(""), str.GetBuffer(200), 200, iniFile);
		str.ReleaseBuffer();
		m_strFilePath = str;
	}
}