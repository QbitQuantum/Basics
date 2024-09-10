// -----------------------------------------------------------------------------
// CCommonTestClass::MpxAttStreamingL()
// Returns: Symbian OS errors.
// -----------------------------------------------------------------------------
TInt CCommonTestClass::MpxAttStreamingL(CStifItemParser& aItem)
    {
    FTRACE(FPrint(_L("CCommonTestClass::MpxAttStreamingL testing TMPXAttribute ExternalizeL and InternalizeL begin")));
    iLog->Log(_L("CCommonTestClass::MpxAttStreamingL testing TMPXAttribute ExternalizeL and InternalizeL begin"));
    TInt err=KErrNone;
    TUint index;
    
    // read in parameters
    if ( aItem.GetNextInt(index) )
        {
        iLog->Log(_L("Missing Parameter: index."));
        return KErrBadTestParameter;
        }
    if ( index >= iMPXAttArray.Count() )
        {
        iLog->Log(_L("Bad Parameter: index out of range."));
        return KErrBadTestParameter;
        }
    
    FTRACE(FPrint(_L("CCommonTestClass::MpxAttStreamingL started ExternalizeL")));
    iLog->Log(_L("CCommonTestClass::MpxAttStreamingL started ExternalizeL"));
    CBufBase* buffer = CBufFlat::NewL( 50 );
    CleanupStack::PushL( buffer );
    RBufWriteStream writeStream( *buffer );
    CleanupClosePushL( writeStream );
    iMPXAttArray[index].ExternalizeL( writeStream );
    writeStream.CommitL();
    buffer->Compress();
    CleanupStack::PopAndDestroy( &writeStream );

    FTRACE(FPrint(_L("CCommonTestClass::MpxAttStreamingL started InternalizeL")));
    iLog->Log(_L("CCommonTestClass::MpxAttStreamingL started InternalizeL"));
    RBufReadStream readStream( *buffer );
    CleanupClosePushL( readStream );                
    TMPXAttribute att;
    att.InternalizeL( readStream );
    CleanupStack::PopAndDestroy( &readStream );
    CleanupStack::PopAndDestroy( buffer );
    
    // verify streaming was correct
    if ( !TMPXAttribute::Match(att, iMPXAttArray[index]) )
        {
        iLog->Log(_L("Streaming Failed Verification."));
        err = KErrUnexpectedValue;
        }
    return err;
    }