//-------------------------------------------------------------------//
// MoveColor()																			//
//-------------------------------------------------------------------//
// This function will "move" the first color away from the second
// color so that they no longer match.  See bColorMatches()
// for the definition of "match".
//
// The resulting color is returned.
//-------------------------------------------------------------------//
void MoveColor( int& nRGB1, const int nRGB2, const int nAllowableSpread )
{
	if ( bColorMatches( nRGB1, nRGB2, nAllowableSpread ) )
	{
		int nRed		= GetRFromRGB( nRGB1 );
		int nGreen	= GetGFromRGB( nRGB1 );
		int nBlue	= GetBFromRGB( nRGB1 );
	//	int nAlpha	= GetAFromRGB( nRGB1 );

		int nBaseRed	= GetRFromRGB( nRGB2 );
		int nBaseGreen	= GetGFromRGB( nRGB2 );
		int nBaseBlue	= GetBFromRGB( nRGB2 );
	//	int nNewAlpha	= GetAFromRGB( nRGB2 );

		if ( abs( GetRFromRGB( nRGB1 ) - GetRFromRGB( nRGB2 ) ) <= nAllowableSpread ) { nRed	= GetColorAdjustment( nRed		, nBaseRed	, nAllowableSpread ); }
		if ( abs( GetGFromRGB( nRGB1 ) - GetGFromRGB( nRGB2 ) ) <= nAllowableSpread ) { nGreen	= GetColorAdjustment( nGreen	, nBaseGreen, nAllowableSpread ); }
		if ( abs( GetBFromRGB( nRGB1 ) - GetBFromRGB( nRGB2 ) ) <= nAllowableSpread ) { nBlue	= GetColorAdjustment( nBlue	, nBaseBlue	, nAllowableSpread ); }
	//	if ( abs( GetAFromRGB( nRGB1 ) - GetAFromRGB( nRGB2 ) ) <= nAllowableSpread ) { nAlpha	= GetColorAdjustment( nAlpha	, nBaseAlpha, nAllowableSpread ); }

		// Now rebuild.
		nRGB1 = CombineRGB( nRed, nGreen, nBlue );

	}

}