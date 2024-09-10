// -----------------------------------------------------------------------------
// AppendBufL
// -----------------------------------------------------------------------------
//
void AppendBufL( TPtr8& aDest, HBufC* aSrc )
    {
    TInt length = aSrc ? aSrc->Length() * 2 : KNullBuffer;

    APPEND_BUF_INT( aDest, length );

    if( length > 0 )
        {
        TPtr8 tmp8( (TUint8*)aSrc->Ptr(), length, length);
        __ASSERT_DEBUG( (aDest.MaxLength() - aDest.Length()) > tmp8.Length() , User::Panic( KNullDesC, KErrTooBig ) );
        aDest.Append( tmp8 );
        }
    }