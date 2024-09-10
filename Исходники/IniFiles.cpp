//----------------------------------------------------------------------------
//class TMemIniFile : public TCustomIniFile
//----------------------------------------------------------------------------
// TIniFileのバグ回避版らしい・・・が、TIniFileと同じことをやる。ドン
TMemIniFile::TMemIniFile(const AnsiString& str) : m_pStream(NULL), m_pConfig(NULL)
{
	if ( str.AnsiPos("\\\\?\\") )
		m_strIniFile = str.SubString( 4, str.Length() - 4).c_str();
	else
		m_strIniFile = str.c_str();
//	m_pStream = new wxFileInputStream( m_strIniFile );
//	m_pConfig = new wxFileConfig(*m_pStream);

//	m_pConfig = new wxFileConfig(wxEmptyString, wxEmptyString, m_strIniFile, wxEmptyString, wxCONFIG_USE_LOCAL_FILE);
	m_pConfig = new wxFileConfig(wxT("krkr"), wxT("ym"), m_strIniFile, wxEmptyString, wxCONFIG_USE_LOCAL_FILE);
}