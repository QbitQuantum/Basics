/** Compare the various character sets
@test
*/		
void CTestHtmlToCrtConverterBufferStep::ComparisonForVariousCharsetsL()
	{
	// Get different character sets from the ini file
	TPtrC	sourceData;
	GetStringFromConfig(ConfigSection(), KSourceText, sourceData);
	
	HBufC8*	tempSource = HBufC8::NewLC(sourceData.Length());
	tempSource->Des().Copy(sourceData);
	TPtr8	source(tempSource->Des());
	
	// Compare the source text with the text converted by the characterset converter
	if ( DoComparisonL(source) == 0 )
		{
		INFO_PRINTF1(KInfoComparisionSuccessful);
		}
	else
		{
		ERR_PRINTF1(KErrInComparison);
		SetTestStepResult(EFail);
		}
	CleanupStack::PopAndDestroy(tempSource);
	}