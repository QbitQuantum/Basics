EXPORT_C HBufC* CResourceLoader::Load2L( TInt aResourceId )
    {
    HBufC8* readBuffer = iResFile.AllocReadLC( aResourceId );
    const TPtrC16 ptrReadBuffer( ( TText16* ) readBuffer->Ptr(), ( readBuffer->Length()+1 )>>1 );
    HBufC16* textBuffer=HBufC16::NewL( ptrReadBuffer.Length() );
    *textBuffer=ptrReadBuffer;
    CleanupStack::PopAndDestroy( readBuffer );
    return textBuffer;
    }