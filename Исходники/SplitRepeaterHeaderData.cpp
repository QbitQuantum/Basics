void CSplitRepeaterHeaderData::setMyCall2(const wxString& my2)
{
	::memset(m_myCall2, ' ', SHORT_CALLSIGN_LENGTH);

	for (unsigned int i = 0U; i < my2.Len(); i++)
		m_myCall2[i] = my2.GetChar(i);
}