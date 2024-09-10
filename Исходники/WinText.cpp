//--------------------------------------------------------------------
void FK2DEngine::FKDrawText( CBitmap& p_Bitmap, const std::wstring& p_Text, int p_nX, 
	int p_nY, CColor p_Color, const std::wstring& p_FontName, 
	unsigned int p_unFontHeight, unsigned int p_unFontFlags /* = 0 */ )
{
	unsigned int unWidth = TextWidth( p_Text, p_FontName, p_unFontHeight, p_unFontFlags );

	CWinBitmap helper( unWidth, p_unFontHeight );
	helper.SelectFont( p_FontName, p_unFontHeight, p_unFontFlags );

	if( ::SetTextColor( helper.Context(), 0xffffff ) == CLR_INVALID )
	{
		Win::ThrowLastError( "设置文字颜色" );
	}
	Win::Check( ::SetBkColor( helper.Context(), TRANSPARENT ), "设置文字图片背景颜色为透明" );

	::ExtTextOut( helper.Context(), 0, 0, 0, 0, p_Text.c_str(), p_Text.length(), 0 );

	for( unsigned int relY = 0; relY < p_unFontHeight; ++relY )
	{
		for( unsigned int relX = 0; relX < unWidth; ++relX )
		{
			CColor pixel = p_Color;
			CColor::Channel srcAlpha = GetPixel( helper.Context(), relX, relY ) & 0xff;
			if( srcAlpha == 0 )
			{
				continue;
			}
			pixel = Multiply( p_Color, CColor( srcAlpha, 255, 255, 255 ) );
			if( pixel != 0 && p_nX + relX >= 0 && p_nX + relX < p_Bitmap.Width()
				&& p_nY + relY >= 0 && p_nY + relY < p_Bitmap.Height() )
			{
				p_Bitmap.SetPixel( p_nX + relX, p_nY + relY, pixel );
			}
		}
	}
}