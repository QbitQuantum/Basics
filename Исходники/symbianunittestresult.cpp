// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
//
void CSymbianUnitTestResult::AddFailureL(
    const TDesC8& aFailureText,
    TInt aAllocFailureRate )
    {
    CSymbianUnitTestFailure* failure = NULL;
    if ( aAllocFailureRate > 0 )
        {
        const TInt KLength = 
            aFailureText.Length() + 
            KSymbianUnitTestAllocFailureRateFormat().Length() + 
            KMax64BitUintLengthAsDescriptor;
        HBufC8* failureMsg = HBufC8::NewLC( KLength );
        failureMsg->Des() = aFailureText;
        failureMsg->Des().AppendFormat(
            KSymbianUnitTestAllocFailureRateFormat, aAllocFailureRate );
        failure = CSymbianUnitTestFailure::NewL( 
            *iCurrentTestName, *failureMsg, KErrNotFound, KNullDesC8 );
        CleanupStack::PopAndDestroy( failureMsg );
        CleanupStack::PushL( failure );
        }
    else
        {
        failure = CSymbianUnitTestFailure::NewLC( 
            *iCurrentTestName, aFailureText, KErrNotFound, KNullDesC8 );
        }
        
    TBuf8<KMaxLength> strLine;
    strLine.Format( KSymbianUnitTestFailed, &aFailureText );
    while(strLine.Length() > 120) 
        {
        TBuf8<KMaxLength> line = strLine.MidTPtr( 0, 120 );
        line.Append( '-' );
        SUT_LOG_FORMAT(_L8("%S"), &line );
        line = strLine.Mid( 120 );
        strLine = line;
        }
    SUT_LOG_FORMAT(_L8("%S"), &strLine );
    //SUT_LOG_FORMAT(KSymbianUnitTestFailed, &aFailureText);
    iCurrentResult = EFalse;
    iFailures.AppendL( failure );
    CleanupStack::Pop( failure ); 
    }