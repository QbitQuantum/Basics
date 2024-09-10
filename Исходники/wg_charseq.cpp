WgCharSeqLiteral::WgCharSeqLiteral( const std::wstring& str, int ofs, int len )
{
	const wchar_t * p = str.c_str();
	int strlen = str.length();

	if( ofs + len > strlen )
	{
		if( ofs > strlen )
			ofs = strlen;
		len = strlen - ofs;
	}

    m_type      = UTF16;
    m_pChar     = p + ofs;
    m_nbChars   = len;
}