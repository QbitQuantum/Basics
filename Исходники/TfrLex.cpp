TPtrC TfrLex::GetL( TLex& aLex, const TChar  aChar )
{
// Skip spaces and mark the token's start point.
aLex.SkipSpace();
TLexMark mark;

aLex.Mark(mark);    

if (aLex.Peek() == '"' )
	{
	// Skip the " and do find next " followed by eos, space or aChar.
	aLex.Inc();
	TChar x;
	while ( x = aLex.Get(), !x.Eos() )
		{
		if ( x == '"' )
			{
			// Found a " character - but is it the end of the token?
			x = aLex.Peek(); // peek the next character
			if ( x.Eos() || x.IsSpace() || x == aChar )
				// End of token: return token.
				return aLex.MarkedToken(mark);
			}
		}
	// Unget and L E A V E because did not find the end " of token.
	aLex.UnGetToMark(mark);
	User::Leave(KErrArgument);
	return aLex.MarkedToken(mark); // never reached (l e a v e).
	}
else
	{
	// Is not a "*" token: find eos or the next space or the aChar
	// and return the token.
	TChar x;
	while ( x = aLex.Peek(), !x.Eos() && !x.IsSpace() && x != aChar )
		aLex.Inc();

	return aLex.MarkedToken(mark);
	}
}