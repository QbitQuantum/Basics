/////////////////////////////////////////////////////////////////////////////
// Set font point size. Convert points to device units
// There are 72 points per inch.
//
zBOOL
ZFontUI::SetFontPointSize( CFont& font, CDC& dc, int pts )
{
   LOGFONT lf;
   font.GetLogFont( &lf );
   lf.lfHeight = MulDiv( -pts, dc.GetDeviceCaps( LOGPIXELSY ), 72 );
   font.DeleteObject( );
   return( font.CreateFontIndirect( &lf ) );
}