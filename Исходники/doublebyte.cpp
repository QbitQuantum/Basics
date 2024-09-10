ucs4_t WXMEncodingDoubleByte::MultiBytetoUCS4(const wxByte* buf)
{
	wxWord dbtmp = (buf[0] << 8) | buf[1];
	ucs4_t uinfo = m_dbfix->MB2UInfo(dbtmp);
	if (uinfo != (ucs4_t)svtUCS4NotCached)
		return uinfo;

	if( IsLeadByte(buf[0]))
		return m_db2u_tab[buf[0]][buf[1]];

	return (buf[1] == '\0')? m_b2u_tab[buf[0]]: (ucs4_t)svtInvaliad;
}