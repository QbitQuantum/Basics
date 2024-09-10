// ----------------------------------------------------------------------------
// ---------- CChatViewerFont
// ----------------------------------------------------------------------------
CChatViewerFont::CChatViewerFont()
{
	name         = "Courier";
	size         = 10;
	codepage     = 0;
	characterSet = 1;
	if ( PRIMARYLANGID(GetSystemDefaultLangID()) == LANG_RUSSIAN ) {
		characterSet = RUSSIAN_CHARSET;
	}

	HFONT hf = (HFONT)::GetStockObject( SYSTEM_FIXED_FONT );
	if ( hf ) {
		CFont* f = CFont::FromHandle( hf );
		if ( f ) {
			LOGFONT lf;
			f->GetLogFont( &lf );
			name         = lf.lfFaceName;
			characterSet = lf.lfCharSet;
		}
	}
}