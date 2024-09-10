// ---------------------------------------------------------
// RFavouritesBuf::Open
// ---------------------------------------------------------
//
TInt RFavouritesBuf::Open( RFavouritesSession& aSess )
    {
	SetBuf( ERead | EWrite, iBuf.iData, iBuf.iData );   // Empty.
    return RFavouritesHandle::Open( aSess, EFavengOpenStream, TIpcArgs() );
    }