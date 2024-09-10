// -----------------------------------------------------------------------------
// CalculateMacL
// -----------------------------------------------------------------------------
//
LOCAL_C HBufC8* CalculateMacL(const TDesC8& aElement, const TDesC8& aMacKey )
    {

    LOG( _L8( "CalculateMacL" ) );
    LOG( _L8( "aMacKey" ) );
    LOGHEX( aMacKey.Ptr(), aMacKey.Length() );
    LOG( _L8( "aElement" ) );
    LOGHEX( aElement.Ptr(), aElement.Length() );
    if( !aMacKey.Length() || !aElement.Length() )
        {
        User::Leave(KErrArgument);
        }

    CHMAC* hMac = NULL;
    CSHA1* sha = NULL;
    TPtrC8 hmac_value( KNullDesC8 );
    TPtrC8 sha1_value( KNullDesC8 );
    HBufC8* macValue = NULL;

    sha = CSHA1::NewL();
    CleanupStack::PushL( sha );
    hMac = CHMAC::NewL( aMacKey, sha );
    CleanupStack::Pop( sha ); // sha is now owned by hMac
    CleanupStack::PushL( hMac );
    hMac->Update( aElement );
    hmac_value.Set( hMac->Final() );

    macValue = hmac_value.AllocL();
    LOG( _L8( "macValue" ) );
    LOGHEX( macValue->Ptr(), macValue->Length() );

    CleanupStack::PopAndDestroy( hMac );
    return macValue;
    }