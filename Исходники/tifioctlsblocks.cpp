//Util function
void CTestIfioctls::ReadStringParam(char* aString)
	{
	_LIT( KSl, "Param%d" );
   	TBuf<8> pNameBuf;
    TPtrC string;
    pNameBuf.Format(KSl,++iParamCount);
	TBool res = GetStringFromConfig(ConfigSection(), pNameBuf, string);
	if(!res)
	 	{
	 	_LIT(Kerr , "Unable to retrieve string parameter") ;
	 	INFO_PRINTF1(Kerr);
	  	}
	TBuf8<256> bufstring;
	bufstring.Copy(string);
	TInt paramLength=string.Length();
	char* text=(char *)(bufstring.Ptr());
 	*(text+paramLength)='\0';
	strcpy(aString,text);
	return;
	}