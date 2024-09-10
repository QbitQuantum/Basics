void CRandomSetSource::GenerateBytesL(TDes8& aDest)
    {
	TInt i=0;
	//Reverse the string by bytes up to the point of the end of the given string
	//of "random" bytes.
    for (i=0; iCounter >= 0 && i< aDest.Length(); ++i,--iCounter)
        {
        aDest[i] = iValue[iCounter];
        }
	//Then fill the remaining (if any) bytes in aDest with 0's.  This is all to
	//allow the stuff to work with bigint style integers; we're writing straight
	//into a RInteger.Ptr() here
	for(;i<aDest.Length(); ++i)
		{
        aDest[i] = 0x00;
		}
    }