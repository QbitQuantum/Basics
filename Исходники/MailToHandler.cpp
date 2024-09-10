// ---------------------------------------------------------
// CMailToHandler::GetNextField()
// ---------------------------------------------------------
//
TInt CMailToHandler::GetNextField( TInt aStart )
    {
	TPtrC path = iParsedUrl->Des();
	TInt retVal = path.Length();
    TPtrC scheme;

    //KSubject KBody KCc
    if( aStart < retVal )
        {
        scheme.Set( path.Right( retVal - aStart ) );
        }
    else
        {
        return retVal;
        }

    TInt subjPos = scheme.FindF( KSubject );
    subjPos = ( subjPos == KErrNotFound ) ? retVal : subjPos;

    TInt bodyPos = scheme.FindF( KBody );
    bodyPos = ( bodyPos == KErrNotFound ) ? retVal : bodyPos;

    TInt toPos = scheme.FindF( KTo );
    toPos = ( toPos == KErrNotFound ) ? retVal : toPos;

    TInt ccPos = scheme.FindF( KCc );
    ccPos = ( ccPos == KErrNotFound ) ? retVal : ccPos;

    TInt bccPos = scheme.FindF( KBcc );
    bccPos = ( bccPos == KErrNotFound ) ? retVal : bccPos;

    TInt temp = Minimum( subjPos, bodyPos, toPos, ccPos, bccPos );
    retVal = ( temp < retVal) ? temp + aStart : retVal;

    return retVal;
    }