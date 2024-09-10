netbios_name::netbios_name(LPCTSTR n, UCHAR type, bool group, UCHAR lana) :
	m_managed (false),
	m_registered (false),
	m_duplicated (false),
	m_error (false),
	m_lana (lana),
	m_listener (NULL),
	m_dgreceiver (NULL),
	m_term (NULL)
{
	// Преобразование имени в NetBIOS-имя
	int len = NCBNAMSZ - 1;
	CT2A nA( n );
	LPCSTR src = (LPCSTR)nA;
	LPSTR dst = (LPSTR)netbiosed.name;
	for ( ; len && *src; --len, ++dst, ++src )
		*dst = *src;
	for ( ; len; --len )
		*dst++ = ' ';
	*dst = (CHAR)type;
	CharUpperBuffA( (LPSTR)netbiosed.name, NCBNAMSZ - 1 );
	CharToOemBuffA( (LPSTR)netbiosed.name, (LPSTR)netbiosed.name, NCBNAMSZ - 1 );
	netbiosed.name_num = 0;
	netbiosed.name_flags = (UCHAR)( group ? GROUP_NAME : UNIQUE_NAME );

	original = GetANSIName();
}