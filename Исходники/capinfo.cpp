// -----------------------------------------------------------------------------
// CCapInfo::AddFormatText( TDes& aText, TInt aNum ) const
// Adds format text
// -----------------------------------------------------------------------------
//
void CCapInfo::AddFormatText( TDes& aText, TInt aNum ) const
    {
    TBuf<KBufSize> buf;
    buf = KNullDesC;

    if ( aNum > KNestingLimit )
        {
        aNum = KNestingLimit;
        }
        
    for ( TInt i=0; i<aNum; i++ )
        {
        buf.Append( KFormatText );
        }
    if ( aText.MaxLength()-aText.Length()>buf.Length() )
        {
        aText.Insert( 0, buf );
        }
    }