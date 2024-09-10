// -----------------------------------------------------------------------------
// CMccCodecRed::SetRedCodecs
// Set the payload types used in redundancy
// -----------------------------------------------------------------------------
//
void CMccCodecRed::SetRedPayloadsL( RArray<TUint>& aRedPayloads )
    {
    iRedPayloads.Reset();
    TInt i;
    for( i = 0; i < aRedPayloads.Count(); i++ )
        {
        iRedPayloads.AppendL( aRedPayloads[ i ] );  
        }
    
    // Convert parsed payload formats back to string and set
    // the iFmtpAttr variable
    const TInt KCharsPerPayload( 4 );
    delete iFmtpAttr;
    iFmtpAttr = NULL;
    iFmtpAttr = HBufC8::NewL( iRedPayloads.Count() * KCharsPerPayload );
    
    TPtr8 descPtr = iFmtpAttr->Des();
    for( i = 0; i < iRedPayloads.Count(); i++ )
        {
        descPtr.AppendNum( static_cast<TUint64>( iRedPayloads[i] ), EDecimal );
        descPtr.Append( KCharSlash );       
        }   
    
    // Remove the last slash character
    descPtr.SetLength( descPtr.Length() - 1 );  
    }