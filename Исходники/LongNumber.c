LongNumber LongMultiplying(LongNumber FirstNumber, LongNumber SecondNumber) 
{
	unsigned long long CurrentBuffer = 0, Multiple;
	LongNumber Result = createNewLongNumber(FirstNumber.Length + SecondNumber.Length);
	
	if (FirstNumber.Sign != SecondNumber.Sign)
		Result.Sign = 1;
	
	int i, j;
	for (i = 0; i < FirstNumber.Length; ++i) 
	{
		for (j = 0; j < SecondNumber.Length || CurrentBuffer; ++j) 
		{
			Multiple = FirstNumber.Digits[i];
			if (j < SecondNumber.Length)
				Multiple *= SecondNumber.Digits[j];
			else
				Multiple = 0;
			CurrentBuffer += Multiple + Result.Digits[i + j];
			lldiv_t FinResult = lldiv(CurrentBuffer, 100000000);
			Result.Digits[i + j] = FinResult.rem;
			CurrentBuffer = FinResult.quot; 
		}
	}
	return removingLeadNulls(Result);	
}