void RLog::Printf(TRefByValue<const TDesC> aFmt,...)
{
	// Logs in the file and calls the Printf Function from the attached  RTest object

	VA_LIST list;
	VA_START(list,aFmt);

	TBuf<0x100> aBuf;
	TBuf8<1024> fBuf;
	aBuf.AppendFormatList(aFmt,list);
	
	if(aBuf.Mid(aBuf.Length() - 1, 1) == _L("\n")){
		aBuf.Insert(aBuf.Length() - 1, _L("\r"));
	}
	
	

	test->Printf(aBuf);
	fBuf.Copy(aBuf);
	TInt r = file.Write(fBuf);	
	
	__ASSERT_ALWAYS(r==KErrNone,User::Panic(_L("Write-Console"),0));

}