	//--------------------------------------------------------------------------------
	int CWString::Format( CWString& Fmt, va_list arglist )
	{
		CStringHelper StringHelper;
		return StringHelper.wvsprintfW( m_p, *(Fmt()), arglist );
	}