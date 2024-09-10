TInt CTestLibcwchar::wmemmove1L(  )
    {

    wchar_t ws1[50]=L"abcdefghij",*retval,ws2[5] = L"abc";
		
	retval = wmemmove(ws1,ws2,3);

	INFO_PRINTF1(_L("wmemmove1 result is"));

	int i;

	for(i=0;i<10;i++)
		{
		INFO_PRINTF5(_L("retval[%d]=%x ws1[%d]=%x"),i,retval[i],i,ws1[i]);
		}

	for(i=0;i<3;i++)
		{
		if(ws1[i] != ws2[i])
			{
			return KErrGeneral;
			}
		}

	return KErrNone;
    
    }