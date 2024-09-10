void CCommandLineDisplay::InputBackspace (void)

//	InputBackspace
//
//	Delete characters from input buffer

	{
	if (m_iCursorPos > 0)
		{
		if (m_iCursorPos == m_sInput.GetLength())
			m_sInput = strSubString(m_sInput, 0, m_sInput.GetLength() - 1);
		else
			m_sInput = strCat(strSubString(m_sInput, 0, m_iCursorPos - 1), strSubString(m_sInput, m_iCursorPos, -1));
		m_iCursorPos--;
		m_bInvalid = true;
		}
	}