void CAgentCtl::ProcessInstruction(const CInstruction& instruction)
{
	USES_CONVERSION;

	if (lstrcmpi(instruction.szCommand, _T("Speak")) == 0)
		SpeakText(CComBSTR(instruction.szText));
	else if (lstrcmpi(instruction.szCommand, _T("Play")) == 0)
		m_pCharacter->Play((BSTR)CComBSTR(instruction.szText), &m_nRequestID);
	else if (lstrcmpi(instruction.szCommand, _T("Hide")) == 0)
		m_pCharacter->Hide(FALSE, &m_nRequestID);
	else if (lstrcmpi(instruction.szCommand, _T("Show")) == 0)
		m_pCharacter->Show(FALSE, &m_nRequestID);
	else if (lstrcmpi(instruction.szCommand, _T("MoveTo")) == 0)
	{
		short x, y;
#ifdef _UNICODE
		wscanf_s(instruction.szText, _T("%d, %d"), &x, &y);
#else
		sscanf_s(instruction.szText, _T("%d, %d"), &x, &y);
#endif
		m_pCharacter->MoveTo(x, y, (100-m_nSpeed)*10+100, &m_nRequestID);
	}
	else if (lstrcmpi(instruction.szCommand, _T("GestureAt")) == 0)
	{
		short x, y;
#ifdef _UNICODE
		wscanf_s(instruction.szText, _T("%d, %d"), &x, &y);
#else
		sscanf_s(instruction.szText, _T("%d, %d"), &x, &y);
#endif
		m_pCharacter->GestureAt(x, y, &m_nRequestID);
	}
}