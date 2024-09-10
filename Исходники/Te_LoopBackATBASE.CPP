void CATBase::ParseBufferLC()
//
//  Parses buffer
//
/**
 * This function is currently not used by the Etel regression test harness.
 */	{
	LOGTEXT(_S8("CATBase Parse the Buffer List"));
	iBuffer.Set(iIo->GetRxBufferLC(iBufferMarker));
	TInt pos=iBuffer.FindF(KOKString);
	if(pos==KErrNotFound)
		{
		LOGTEXT(_S8("CATBase Error - Cannot find OK'"));
		User::Leave(pos);
		}
	//	Place everything before the OK into buffer
	iBuffer.Set(iBuffer.Left(pos));

	TLex8 yyLex(iBuffer);
	TChar peek;
	//	Look for '=' sign and move seeker cursor to the right of it if it exists
	pos=iBuffer.Find(_L8("="));
	if (pos!=KErrNotFound)
		{
		yyLex.Inc(pos+1);
		}
	//	Move cursor past any spaces or open brackets
	yyLex.SkipSpace();
	peek=yyLex.Peek();
	if ((TUint)peek=='(' || (TUint)peek=='[' || (TUint)peek=='{')
		yyLex.Inc();

	yyLex.SkipSpace();
	peek = yyLex.Peek();
	do
		{
		// Search for the next character that is not a comma, and mark it. Keep looking at 
		// subsequent characters until it is a space,comma,closing bracket or end of string.
		// Store the string (between marked character and current character) as an item in
		// an array of CATParamListEntry object pointers.
		if (peek!=',')
			{
			yyLex.Mark();
			do
				{
				yyLex.Inc();
				peek=yyLex.Peek();
				}
			while (peek!=',' && !peek.IsSpace() && peek!=')'&& peek!=']'&& peek!='}' && !yyLex.Eos());
			CATParamListEntry* aParamListEntry = new (ELeave) CATParamListEntry(yyLex.MarkedToken());
			iRxResults.AddLast(*aParamListEntry);
			}
		// Move cursor to the next non-space character, and end the loop if it is a closing
		// bracket or the end of the buffer.
		yyLex.Inc();
		yyLex.SkipSpace();
		peek = yyLex.Peek();
		}
	while (!yyLex.Eos() && peek!=')'&& peek!=']'&& peek!='}');
	}