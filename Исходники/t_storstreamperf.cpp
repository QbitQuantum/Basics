/**
@SYMTestCaseID			PDS-STORE-UT-4056
@SYMTestCaseDesc		Test for DEF141471 - STORE, new stream performance tests.
						PREQ2505 Insturmentation of PDS.
						RBufWriteStream & RBufReadStream performance tests.
@SYMTestPriority		High
@SYMTestActions			Test for DEF141471 - STORE, new stream performance tests.
@SYMTestExpectedResults Test must not fail
@SYMDEF					DEF141471
*/
void BufStreamTestL()
	{
	CBufFlat* bufFlat = CBufFlat::NewL(KTestDataLen);
	CleanupStack::PushL(bufFlat);
	
	//RBufWriteStream::Open()
	RBufWriteStream strm1;
	CleanupClosePushL(strm1);
	TUint32 fc = User::FastCounter();
	strm1.Open(*bufFlat);
	TUint32 openFc = CalcTickDiff(fc, User::FastCounter());
	PrintFcDiffAsUs(_L("###  RBufWriteStream::Open(), Time=%d us\r\n"), openFc);
	DoStreamWriteTestL(strm1);
	CleanupStack::PopAndDestroy(&strm1);
	TheTest.Printf(_L("       Buffer size=%d\r\n"), bufFlat->Size());

	//RBufWriteStream::Append()
	RBufWriteStream strm2;
	CleanupClosePushL(strm2);
	fc = User::FastCounter();
	strm2.Append(*bufFlat);
	TUint32 appendFc = CalcTickDiff(fc, User::FastCounter());
	PrintFcDiffAsUs(_L("###  RBufWriteStream::Append(), Time=%d us\r\n"), appendFc);
	DoStreamWriteTestL(strm2);
	CleanupStack::PopAndDestroy(&strm2);
	TheTest.Printf(_L("       Buffer size=%d\r\n"), bufFlat->Size());
	
	//RBufWriteStream::Insert()
	RBufWriteStream strm3;
	CleanupClosePushL(strm3);
	fc = User::FastCounter();
	strm3.Insert(*bufFlat, KBufSize);
	TUint32 insertFc = CalcTickDiff(fc, User::FastCounter());
	PrintFcDiffAsUs(_L("###  RBufWriteStream::Insert(), Time=%d us\r\n"), insertFc);
	DoStreamWriteTestL(strm3);
	CleanupStack::PopAndDestroy(&strm3);
	TheTest.Printf(_L("       Buffer size=%d\r\n"), bufFlat->Size());
	
	//RBufWriteStream::Truncate()
	RBufWriteStream strm4;
	CleanupClosePushL(strm4);
	fc = User::FastCounter();
	strm4.Truncate(*bufFlat);
	TUint32 truncateFc = CalcTickDiff(fc, User::FastCounter());
	PrintFcDiffAsUs(_L("###  RBufWriteStream::Truncate(), Time=%d us\r\n"), truncateFc);
	DoStreamWriteTestL(strm4);
	CleanupStack::PopAndDestroy(&strm4);
	TheTest.Printf(_L("       Buffer size=%d\r\n"), bufFlat->Size());
	
	RBufReadStream strm5;
	CleanupClosePushL(strm5);
	fc = User::FastCounter();
	strm5.Open(*bufFlat);
	openFc = CalcTickDiff(fc, User::FastCounter());
	PrintFcDiffAsUs(_L("###  RBufReadStream::Open(), Time=%d us\r\n"), openFc);
	DoStreamReadTestL(strm5);
	CleanupStack::PopAndDestroy(&strm5);
	
	CleanupStack::PopAndDestroy(bufFlat);
	}