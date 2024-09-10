TInt CIniFileParser::GetNextTokenAndCheck(TLex8& lex, TPtr8& tempPtr)
/*
Gets next token and ensures the token is simply not the EOF or a linefeed.
lex is the lexical string to get the next token from.
tempPtr points to the next token
Returns KErrGeneral if token is bad or if we've already read past the end.
*/
	{
	TUint8 ch;
	TInt len;

	if (lex.Eos())
		{
		return KErrGeneral;
		}
	
	tempPtr = lex.NextToken();

	len = tempPtr.Length();
	if (len == 0)
		{
		// lex has figured out what is left is just the EOF
		return KErrGeneral;
		}

	// this next part may be superfluous but we've had so much strife with
	// the parser thus far that for now we're leaving it in

	ch = tempPtr[0];
	if (ch == KCarriageReturn || ch == KLineFeed)
		{
		return KErrGeneral;
		}

	if (tempPtr.Length() < 2)
		{
		return KErrNone;
		}
	ch = tempPtr[1];
	if (ch == KCarriageReturn || ch == KLineFeed)
		{
		return KErrGeneral;
		}

	return KErrNone;
	}