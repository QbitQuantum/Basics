Base::Math::CVector2	CRendererDX::GetTextExtent( spCBaseFont _spFont, const std::string &_text )
{
    ASSERT( _text != "" );

	Base::Math::CVector2 result;

	if( _spFont == NULL )
		return result;

	uint32 width = 0;
    uint32 height = 0;

	fp4	dispWidth  = (fp4)m_spDisplay->Width();
    fp4	dispHeight = (fp4)m_spDisplay->Height();

	spCFontDX	spDXFont = _spFont;
	ID3DXFont	*pDXFont = spDXFont->GetDXFont();
    ASSERT( pDXFont );

    //	Make a copy of `text' and extend it by `.'.
	size_t textLength = _text.length();
	ASSERT( textLength < 2048 );

	static char	pTmp[ 2048 ];
    strcpy( pTmp, (const char *)_text.c_str() );
    pTmp[ textLength ] = '.';
    pTmp[ textLength + 1 ] = '\0';

    //	Determine extents of `.'.
    RECT dotRect = { 0, 0, 0, 0 };
    int32 h = pDXFont->DrawTextA( NULL, ".", -1, &dotRect, DT_LEFT | DT_NOCLIP | DT_CALCRECT, 0 );
    int32 dotWidth = dotRect.right - dotRect.left;

    RECT rect = { 0, 0, 0, 0 };
    h = pDXFont->DrawTextA( NULL, pTmp, -1, &rect, DT_LEFT | DT_NOCLIP | DT_CALCRECT, 0 );

    width = rect.right - rect.left - dotWidth;
    height = rect.bottom - rect.top;

	result = Base::Math::CVector2( (fp4(width) / dispWidth), (fp4(height) / dispHeight) );

	return( result );
}