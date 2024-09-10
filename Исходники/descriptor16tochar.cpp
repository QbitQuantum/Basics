EXPORT_C int Tptr16ToCharp (const TDes16& aSrc, char* aDes, int& n_size)
{
    unsigned int ilen = 0 ;
    int retval = ESuccess;
    ilen = aSrc.Length();
    wchar_t* temp16String = NULL;
    int minusone = -1;
    
	if ( !aDes )
    {
        return EInvalidPointer;
    }
    else if (n_size < ilen*2+1)
    {
    	n_size = ilen*2 + 1;
    	return EInvalidSize;
    }
    
    temp16String = new wchar_t [ilen+1];
	if (!temp16String)
	{
		return EInsufficientSystemMemory;
	}
	
	wmemcpy(temp16String, (const wchar_t *)aSrc.Ptr(), ilen);
	temp16String[ilen] = L'\0'; 
	
	if(minusone != wcstombs(aDes, temp16String, ilen*2))
	{
	     aDes[ilen*2] = '\0';    
	}
	else 
	{
		retval = EInvalidWCSSequence;
	}
	
	delete []temp16String;
	return retval;
}