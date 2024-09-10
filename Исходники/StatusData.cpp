CStatusData::CStatusData(const wxString& text, unsigned int n) :
m_data(NULL),
m_n(n),
m_address(),
m_port(0U)
{
	m_data = new unsigned char[20U];
	::memset(m_data, ' ', 20U);

	for (unsigned int i = 0U; i < text.Length() && i < 20U; i++)
		m_data[i] = text.GetChar(i);
}