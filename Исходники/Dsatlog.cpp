void CDTSYLogger::WriteFormat(TRefByValue<const TDesC8> aFmt,...)
	{
	TBuf8<KGenericBufferSize> buf;
    VA_LIST list;
    VA_START(list,aFmt);
    buf.FormatList(aFmt,list);
	TChar tmpchar;
	for(TInt i=0;i<buf.Length();i++)
		{
		tmpchar=buf[i];
		if(!((tmpchar.IsPrint()) || (tmpchar=='\n') || (tmpchar=='\r') || (tmpchar=='\t')))
			buf[i]='.';
		}
#ifdef __EXE__
	CDTSYLogger* context=aScriptLoggerContext;
#else
	CDTSYLogger* context=(CDTSYLogger*) Dll::Tls();
#endif
	if(context==NULL)
		{
		TRAPD(ret,context=CDTSYLogger::NewL());
		if (ret==KErrNone)
			{	
#ifdef __EXE__
			aScriptLoggerContext=context;
#else
			Dll::SetTls(context);
#endif
			}
		else return;
		}
	if(context->iValid)
		context->WriteRecord(buf);
	}