EXPORT_C int Tptr8ToWcharp(const TPtr8& aSrc, wchar_t* aDes, int& n_size)
{
   
    int retval = ESuccess;
    unsigned int ilen = aSrc.Length();
    int minusone = -1;
    
    if (0 == ilen)
    {
    	return EDescriptorNoData;
    }
    else if(!aDes)
    {
    	return EInvalidPointer;
    } 
	else if(n_size < ilen+1)
    {
        n_size = ilen+1 ;
    	return EInvalidSize;
    }
	
	if(minusone != mbstowcs(aDes, (const char*)aSrc.Ptr(), ilen))
	{
	    aDes[ilen] = L'\0';
	}
	else 
	{
		retval = EInvalidMBSSequence;
	}
	
	return retval;
}