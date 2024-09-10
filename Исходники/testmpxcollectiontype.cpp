// -----------------------------------------------------------------------------
// CCommonTestClass::ExternalizeMPXCollectionTypeL()
// Returns: Symbian OS errors.
// -----------------------------------------------------------------------------
TInt CCommonTestClass::ExternalizeMPXCollectionTypeL()
    {
	FTRACE(FPrint(_L("CCommonTestClass::ExternalizeMPXCollectionTypeL testing CMPXCollectionType::ExternalizeMPXCollectionTypeL begin")));
    iLog->Log(_L("CCommonTestClass::ExternalizeMPXCollectionTypeL testing CMPXCollectionType::ExternalizeMPXCollectionTypeL begin"));
    TInt err = KErrNone;
    if ( iType != NULL )
        {
    	FTRACE(FPrint(_L("CCommonTestClass::ExternalizeMPXCollectionTypeL started Externalize")));
        iLog->Log(_L("CCommonTestClass::ExternalizeMPXCollectionTypeL started Externalize"));
        CBufBase* buffer = CBufFlat::NewL( 50 );
        CleanupStack::PushL( buffer );
        RBufWriteStream writeStream( *buffer );
        CleanupClosePushL( writeStream );
        iType->ExternalizeL( writeStream );
        writeStream.CommitL();
        buffer->Compress();
        CleanupStack::PopAndDestroy( &writeStream );
        CleanupStack::PopAndDestroy( buffer ); 
        }
    else
        {
        err = KErrBadTestParameter;
    	FTRACE(FPrint(_L("CCommonTestClass::ExternalizeMPXCollectionTypeL Stif test script is wrong.")));
        iLog->Log(_L("CCommonTestClass::ExternalizeMPXCollectionTypeL Stif test script is wrong."));
        }
	FTRACE(FPrint(_L("CCommonTestClass::ExternalizeMPXCollectionTypeL testing CMPXCollectionType::ExternalizeMPXCollectionTypeL end err=%d"), err));
    iLog->Log(_L("CCommonTestClass::ExternalizeMPXCollectionTypeL testing CMPXCollectionType::ExternalizeMPXCollectionTypeL end err=%d"), err);
	return err;
    }