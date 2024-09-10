// *************************************************************************
// Draw an item on the screen
// *************************************************************************
static void DrawItem( char* Name, int y, long Price )
{
	int j;

	FntSetFont( stdFont );
	DrawChars( Name, 30, y );

	EraseRectangle( 110, y, 56, 9 );
	StrIToA( SBuf, Price );
	StrCat( SBuf, " cr." );
	
	j = MAXDIGITS - StrLen( SBuf );
	if (Price > 0)
		DrawChars( SBuf, 124+j*5, y );
	else
		DrawChars( "not sold", 122, y );
}