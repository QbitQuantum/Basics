void CCmd_MaxChange::OnOutputInfo(char level, LPCTSTR data, LPCTSTR msg)
{
	// A 'P4 Changes' row - just get the change number 
    LPCTSTR p = StrStr(data, _T("Change"));
    if(p)
	{
        // find the change number
        static TCHAR digits[] = _T("0123456789");

        int posDigits = StrCSpn(data, digits);
        if(posDigits || _istdigit(data[0]))
		{
            m_MaxChange = _ttoi(data+posDigits);
		}
	}
	else
		CP4Command::OnOutputInfo(level, data, msg);
}