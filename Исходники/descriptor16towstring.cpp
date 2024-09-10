EXPORT_C int Tbuf16ToWstring(TDes16& aSrc, wstring& aDes)
{	
   
    unsigned int ilen = aSrc.Length();
    if (0 == ilen)
	{
		return EDescriptorNoData;
	}
	
	wchar_t* wcharString = new wchar_t[ilen+1];
	if (!wcharString)
	{
		return EInsufficientSystemMemory;
	}
	
	wmemcpy((wchar_t*)wcharString, (const wchar_t*)aSrc.Ptr(), ilen);
	wcharString[ilen] = L'\0';
	
	aDes.assign(wcharString);
	
	delete []wcharString;
	return ESuccess;
}