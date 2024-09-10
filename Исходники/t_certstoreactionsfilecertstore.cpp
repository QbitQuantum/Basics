void CCreateFileCertStore::ConstructL(const TTestActionSpec& aTestActionSpec)
	{
	CCertStoreTestAction::ConstructL(aTestActionSpec);
	TInt err = KErrNone;
	TInt pos = 0;
	TPtrC8 fileName = Input::ParseElement(aTestActionSpec.iActionBody, KFileNameStart, 
		KFileNameEnd, pos, err);
	iFileName = HBufC::NewL(fileName.Length());
	iFileName->Des().Copy(fileName);
	
	// Set expected result
	pos = 0;
	
	HBufC* result = HBufC::NewLC(aTestActionSpec.iActionResult.Length());
	TPtr(result->Des()).Copy(aTestActionSpec.iActionResult);
	Input::GetExpectedResultL(Input::ParseElement(*result, KReturnStart, KReturnEnd), iExpectedResult);
	CleanupStack::PopAndDestroy(result);
	}