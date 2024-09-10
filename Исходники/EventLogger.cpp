void CEventLogger :: SWrite(const TDesC& aModuleName, const TDesC& aMessage)
{
	RFileLogger iLogger;
	iLogger.Connect();
	iLogger.CreateLog(KLogDir,KLogFile,EFileLoggingModeAppend);

	_LIT(CrLfValue,"\r\n");
	TBuf<5> CrLf;
	CrLf.Format(_L("%S"),&CrLfValue);

	_LIT(hyp,"-");
	TBuf<2> Hyphen;
	Hyphen.Format(_L("%S"),&hyp);				

	TInt MessageLen,ModuleNameLen,MessageToLogLen;
	MessageLen = ModuleNameLen = MessageToLogLen = 0;

	MessageLen = aMessage.Length();
	ModuleNameLen = aModuleName.Length();

	MessageToLogLen = ModuleNameLen;
	MessageToLogLen += Hyphen.Length();
	MessageToLogLen += MessageLen;
	MessageToLogLen += CrLf.Length();

	HBufC* MessageToLog = HBufC :: NewLC(MessageToLogLen);

	MessageToLog->Des().Copy(aModuleName);
	MessageToLog->Des().Append(Hyphen);
	MessageToLog->Des().Append(aMessage);
	MessageToLog->Des().Append(CrLf);

	iLogger.Write(*MessageToLog);

	CleanupStack::PopAndDestroy(MessageToLog);

	iLogger.CloseLog();
	iLogger.Close();
}