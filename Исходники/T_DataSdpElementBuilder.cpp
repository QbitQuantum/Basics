/**
Test MSdpElementBuilder::BuildURLL()
*/
void CT_DataSdpElementBuilder::DoCmdBuildURLL(MSdpElementBuilder& aElementBuilder, const TDesC& aSection)
{
    iDataWrapper.INFO_PRINTF1(_L("MSdpElementBuilder BuildURLL Call"));

    TPtrC 								theString;
    if( iDataWrapper.GetStringFromConfig(aSection, KUrl(), theString) )
    {
        HBufC8*	theString8=HBufC8::NewLC(theString.Length());
        theString8->Des().Copy(theString);
        TPtrC8	stringPtr = theString8->Des();
        TRAPD(err, aElementBuilder.BuildURLL(stringPtr));
        if(err != KErrNone)
        {
            iDataWrapper.ERR_PRINTF2(_L("MSdpElementBuilder BuildURLL failed with error %d"), err);
            iDataWrapper.SetError(err);
        }
        CleanupStack::PopAndDestroy(theString8);
    }
    else
    {
        iDataWrapper.ERR_PRINTF2(_L("Missing parameter %S"), &KUrl());
        iDataWrapper.SetBlockResult(EFail);
    }
}