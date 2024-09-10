// -----------------------------------------------------------------------------
// CUpnpHttpChunkParser::ParseL
// Decoding the chunked-encoded buffer
// -----------------------------------------------------------------------------
//
TBool CUpnpHttpChunkParser::ParseExtension( TDes8& aBuffer, TInt& aPos )
    {	
    if ( IsEmpty( aBuffer, aPos ) )
        {	    
        return ETrue;	
        }

    //if '\r\n' exists
    TInt lineFeed = aBuffer.Right( aBuffer.Length() - aPos ).FindF( UpnpString::KLineFeed );
    if ( lineFeed != KErrNotFound )
        {
        aBuffer.Delete( aPos, lineFeed + UpnpString::KLineFeed().Length() );		
        if ( !iChunkSize )
            {
            iContext = ETrailer;
            return EFalse;		
            }
        else
            {
            iContext = EBody;
            return EFalse;
            }		
        }
    else
        {
        //one character left - possible linefeed
        if ( aPos + 1 < aBuffer.Length() )
            {            
            aBuffer.Delete( aPos, aBuffer.Length() - aPos - 1 );
            }
        return ETrue;
        }
    }