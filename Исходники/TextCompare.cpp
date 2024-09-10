void CLine::hash_string(const std::_tstring & s)
{
	// Calc Hash
	boost::crc_32_type computer;
	computer.reset();
	computer.process_bytes(s.c_str(), sizeof(TCHAR) * s.length());
	m_hash = computer.checksum();

	// Calc Anchor Hash
	bool prevIsGraph = true;
	static boost::crc_32_type anchorComputer;
	anchorComputer.reset();
	for (unsigned int i = 0; i < s.length(); ++i)
	{
		bool isGraph = iswgraph(s[i]) != 0 || s[i] == '\r' || s[i] == '\n';
		if (isGraph)
			anchorComputer.process_bytes(&s[i], sizeof(TCHAR));
		prevIsGraph = isGraph;
	}
	m_anchorHash = anchorComputer.checksum();
}