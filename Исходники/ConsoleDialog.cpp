void ConsoleDialog::runStatement()
{
	assert(m_console != NULL);
	if (m_console)
	{
		
		HWND hText = ::GetDlgItem(_hSelf, IDC_INPUT);
		size_t length = GetWindowTextLengthW(hText);
		TCHAR *buffer = new TCHAR[length + 1];
		GetWindowText(hText, buffer, length + 1);
		historyAdd(buffer);
		std::shared_ptr<char> charBuffer = WcharMbcsConverter::tchar2char(buffer);
		delete [] buffer;

		writeText(m_prompt.size(), m_prompt.c_str());
		writeText(strlen(charBuffer.get()), charBuffer.get());
		writeText(1, "\n");
		SetWindowText(hText, _T(""));
		m_console->runStatement(charBuffer.get());
	}
}