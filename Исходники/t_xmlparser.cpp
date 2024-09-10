/**
@SYMTestCaseID 		 		SYSLIB-XML-CT-3738
@SYMTestCaseDesc		    Parser copes with leaving content handler.
@SYMTestPriority 		    Medium
@SYMTestActions  		    Checks that the parser copes with a leave from a content handler callback.
@SYMTestExpectedResults 	Tests pass.
@SYMPREQ 		 		 	PREQ230
*/
LOCAL_C void CallbackLeaveTestL()
	{
	TSimpleContentHandler contentHandler;
	contentHandler.iLeaveOnStartElement = ETrue;

	CParser* parser = CParser::NewLC(KParserDataType, contentHandler);

	RFs fs;
	User::LeaveIfError(fs.Connect());
	CleanupClosePushL(fs);

	TRAPD(err, ParseL(*parser, fs, KSimpleTestFile()));

	User::LeaveIfError(err); // For OOM testing

	test(contentHandler.iNumElements==1);
	test(err==TSimpleContentHandler::KExpectedLeaveCode);

	contentHandler.iLeaveOnStartElement = EFalse;
	ParseL(*parser, fs, KSimpleTestFile());
	test(contentHandler.iNumElements==6);

	CleanupStack::PopAndDestroy(2);
	}