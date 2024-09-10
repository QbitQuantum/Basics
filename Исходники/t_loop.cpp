void CTestXonXoff::WriteComplete(TInt aStatus)
	{
	if (iTrace)
		{
		Test.Printf(_L("CTestXonXoff::WriteComplete(%d) len = %d/%d (%d)\r\n"), aStatus, iWriter->iDes.Length(), iWriter->iDes.MaxLength(), iWriter->iTotal);
		}

	if (aStatus!=KErrNone)
		{
		Fail(ETestFailWrite, aStatus);
		return;
		}

	switch (iState)
		{
	case EWaitReady:
		iRetries = 0;
		iTimer->Cancel();
		iState = EWaitIO;
		Test.Printf(_L("Port Ready\r\n"));
		LineFailOn();
		iStartTime.UniversalTime();;
		Write();
		Read();
		break;
	case EWaitIO:
		iRetries = 0;
		Write();
		break;
	default:
		break;
		}
	}